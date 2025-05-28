import asyncio
import os

from code_generator_async import code_generator_async
from code_repairer_async import code_repairer_async
from config import CONFIG, ANSWERS_SAVE_DIR
from crawler_oj import crawl_problems
from fault_locator_async import fault_locator_async
from local_test import local_test
from online_judge_async import online_judge_async
from utils import login_buctoj, load_problems


async def code_generate_workflow_async(problem, cpp_file_path, generate_turn):
    problem_id = problem["idx"]

    print(f"⏳ 题目 {problem_id} 第 {generate_turn} 次代码生成开始")
    code, code_generate_messages = await code_generator_async(problem)
    print(f"✅ 题目 {problem_id} 代码生成完成")

    if code is None:
        print(f"❌ 题目 {problem_id} 代码生成失败")
        return False

    # 保存代码
    with open(cpp_file_path, "w", encoding="utf-8") as f:
        f.write(code)
    print(f"✅ 已保存题目 {problem_id} 代码到 {cpp_file_path}")
    return True


async def code_fault_locate_and_repair_workflow_async(problem, cpp_file_path, error_message):
    problem_id = problem["idx"]

    # 读取待修复代码
    with open(cpp_file_path, "r", encoding="utf-8") as f:
        code = f.read()

    print(f"⏳ 题目 {problem_id} 开始缺陷分析")
    fault_locator_advise, fault_locator_messages = await fault_locator_async(problem, code, error_message)
    print(f"✅ 题目 {problem_id} 缺陷分析完成")

    print(f"⏳ 题目 {problem_id} 开始代码修复")
    code, code_repair_messages = await code_repairer_async(problem, code, error_message, fault_locator_advise)
    if code is None:
        print(f"❌ 题目 {problem_id} 代码修复失败，重新生成代码")
        return False

    # 保存修复后的代码
    with open(cpp_file_path, "w", encoding="utf-8") as f:
        f.write(code)
    print(f"✅ 题目 {problem_id} 代码修复完成，已保存修复后代码到 {cpp_file_path}")
    return True


async def local_test_and_iterative_refinement(problem, cpp_file_path, local_test_turn):
    problem_id = problem["idx"]

    # 测试样例
    sample_input = problem["sample_input"]
    sample_output = problem["sample_output"]
    # 初始化标志变量
    local_test_success = False

    # 本地测试循环
    while local_test_turn < CONFIG["max_local_test_turn"]:
        # 本地测试次数加1
        local_test_turn += 1
        print(f"⏳ 题目 {problem_id} 第 {local_test_turn} 次本地测试开始")
        local_test_success, local_test_error = local_test(cpp_file_path, sample_input, sample_output)

        if local_test_success:
            print(f"✅ 题目 {problem_id} 本地测试通过")
            return True, local_test_turn

        print(f"❌ 题目 {problem_id} 本地测试未通过，信息:\n{local_test_error}")

        # 如果只反复尝试生成，则跳过缺陷分析和代码修复
        if CONFIG["only_gen_and_retry"]:
            print(f"❌ 题目 {problem_id} 跳过修复，开始重新生成代码")
            return False, local_test_turn
        else:
            # 缺陷分析和代码修复
            fault_locate_and_repair_success = await code_fault_locate_and_repair_workflow_async(problem,
                                                                                                cpp_file_path,
                                                                                                local_test_error)
            # 如果代码修复失败，则退出本地测试
            if not fault_locate_and_repair_success:
                return False, local_test_turn

    print(f"❌ 题目 {problem_id} 本地测试未通过达到阈值，开始重新生成代码")
    return False, local_test_turn


async def deal_one_problem_async(session, problem):
    # 获取题目id
    problem_id = problem["idx"]

    # 手动选择题目
    # if problem_id not in [1,5,6]:
    #     return True,  problem_id

    # 代码保存路径
    cpp_file_name = f"problem_{problem_id}.cpp"
    cpp_file_path = os.path.join(ANSWERS_SAVE_DIR, cpp_file_name)

    # 生成代码次数
    generate_turn = 0

    # 生成循环
    while generate_turn < CONFIG["max_generate_turn"]:
        # 生成次数加1
        generate_turn += 1

        # 生成代码
        code_generate_success = await code_generate_workflow_async(problem, cpp_file_path, generate_turn)
        # 代码生成失败
        if not code_generate_success:
            continue  # 回到生成循环

        # —— 本地测试阶段 ——
        # 本地测试次数
        local_test_turn = 0

        # 开始本地测试与迭代优化，累加local_test_turn
        local_test_success, local_test_turn = await local_test_and_iterative_refinement(problem,
                                                                                        cpp_file_path,
                                                                                        local_test_turn)
        # 本地测试未通过，且无法修复或多次修复仍不通过
        if not local_test_success:
            continue  # 回到生成循环

        # —— 在线判题阶段 ——
        # 在线判题次数
        online_judge_turn = 0
        # 在线判题循环
        while online_judge_turn < CONFIG["max_online_judge_turn"]:
            # 在线判题次数加1
            online_judge_turn += 1

            # 读取最新代码
            with open(cpp_file_path, "r", encoding="utf-8") as f:
                code = f.read()

            print(f"⏳ 题目 {problem_id} 提交代码进行在线判题")
            online_judge_success, online_judge_result = await online_judge_async(session, problem_id, code)

            if online_judge_success and online_judge_result == "正确":
                print(f"✅ 题目 {problem_id} 在线判题结束，答案正确")
                return True, problem_id

            elif online_judge_success:
                print(f"🔶 题目 {problem_id} 在线判题结果：{online_judge_result}")

                # 如果只反复尝试生成，则跳过缺陷分析和代码修复
                if CONFIG["only_gen_and_retry"]:
                    print(f"❌ 题目 {problem_id} 跳过修复，开始重新生成代码")
                    break   # 回到生成循环
                else:
                    # 缺陷分析和代码修复
                    fault_locate_and_repair_success = await code_fault_locate_and_repair_workflow_async(
                        problem, cpp_file_path, online_judge_result)

                    # 如果代码修复失败，则跳出在线判题循环
                    if not fault_locate_and_repair_success:
                        break  # 回到生成循环

                    # 再次尝试本地测试，同样是累加local_test_turn
                    local_test_success, local_test_turn = await local_test_and_iterative_refinement(problem,
                                                                                                    cpp_file_path,
                                                                                                    local_test_turn)
                    # 修复后的代码本地测试未通过，且无法修复或多次修复仍不通过，则跳出在线判题循环
                    if not local_test_success:
                        break  # 回到生成循环

            else:
                print(f"❌ 题目 {problem_id} 在线判题失败，信息: {online_judge_result}")
                continue  # 本轮在线判题失败，重新尝试

        # 如果在线判题次数用尽仍未成功
        if online_judge_turn >= CONFIG["max_online_judge_turn"]:
            print(f"❌ 题目 {problem_id} 在线判题失败达到阈值，重新生成代码")
        continue  # 回到代码生成循环

    # 所有生成尝试均失败
    print(f"❌ 题目 {problem_id} 达到最大生成次数，解答失败")
    return False, problem_id


async def process_all_problems(session, problems, max_concurrent=CONFIG["concurrency_limit"]):
    # 创建信号量控制并发数
    semaphore = asyncio.Semaphore(max_concurrent)

    async def sem_task(problem):
        async with semaphore:
            return await deal_one_problem_async(session, problem)

    # 创建所有任务
    tasks = [sem_task(problem) for problem in problems]

    # 并发执行任务
    results = await asyncio.gather(*tasks)

    return results


if __name__ == "__main__":
    # 登录
    session = login_buctoj(CONFIG)
    # 爬取题目
    print("⏳ 开始爬取题目")

    # 我也不知道为什么，考试模式下，并发爬虫爬不到题目
    # 但是绝大部分情况下，都不会出现该bug
    # from crawler_oj_async  import crawl_problems_async
    # problems = crawl_problems_async(session)

    # 如果上面的爬虫报错，请使用下面的顺序爬虫
    # from crawler_oj import crawl_problems
    problems = crawl_problems(session)

    print("✅ 爬取题目完成")
    # 读取题目
    print("⏳ 开始读取题目")
    problems = load_problems()
    print("✅ 读取题目完成")

    # 并发解答所有问题
    results = asyncio.run(process_all_problems(session, problems))

    # 打印结果
    success_count = sum(1 for success, _ in results if success)
    for result in results:
        success, problem_id = result
        if success:
            print(f"✅ 题目 {problem_id} 解答成功")
        else:
            print(f"❌ 题目 {problem_id} 解答失败")
    print(f"✅ 总共成功解答 {success_count}/{len(results)} 个题目")
