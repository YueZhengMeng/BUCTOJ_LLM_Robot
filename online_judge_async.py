import asyncio
import os
import time

from bs4 import BeautifulSoup

from config import CONFIG, SUBMIT_URL, JUDGE_RESULT_DICT, JUDGE_RESULT_URL_TEMPLATE, ANSWERS_SAVE_DIR
from utils import login_buctoj

# 保证同一时间只有一个协程修改last_submit_time
submit_code_limit_lock = asyncio.Lock()
# 上一次提交代码的时间
last_submit_time = 0


def submit_code(session, problem_id, code, language_id, cid):
    files = {"answer": ("code.cpp", code.encode("utf-8")), }
    data = {"cid": cid, "pid": problem_id, "language": language_id, "source": code, "input_text": "",
            "problem_id": problem_id, }

    resp = session.post(SUBMIT_URL, data=data, files=files)
    return resp


async def submit_code_with_limit(session, problem_id, code, language_id, contest_id):
    global submit_code_limit_lock, last_submit_time

    async with submit_code_limit_lock:
        current_time = time.time()
        elapsed = current_time - last_submit_time
        if elapsed < CONFIG["submit_code_delay"]:
            print(f"⏳ 题目 {problem_id} 提交代码被阻塞，需要等待{CONFIG['submit_code_delay'] - elapsed:.2f}秒")
            await asyncio.sleep(CONFIG["submit_code_delay"] - elapsed)

        # 提交代码
        print(f"⏳ 题目 {problem_id} 提交代码开始")
        result = submit_code(session, problem_id, code, language_id, contest_id)
        last_submit_time = time.time()
        return result


async def online_judge_async(session, problem_id, code):
    # 提交代码，同时限制提交代码的频率
    submit_code_response = await submit_code_with_limit(session, problem_id, code, CONFIG["language_id"],
                                                        CONFIG["contest_id"])

    # 检查提交代码请求是否成功
    if submit_code_response.status_code == 200:
        # 使用BeautifulSoup解析HTML
        soup = BeautifulSoup(submit_code_response.text, 'html.parser')

        # 查找表格
        table = soup.find('table', id='table', class_='ui very basic center aligned table')

        # 如果找到表格
        if table:
            # 获取表格中的所有行
            rows = table.find_all('tr')
            # rows[0]是表头，rows[1]是最新一次提交
            first_row_first_cell = rows[1].find('td')
            # 得到submit_id
            submit_id = first_row_first_cell.text.strip()
        else:
            return False, "未找到提交代码结果表格"
    else:
        return False, f"提交代码请求失败，状态码：{submit_code_response.status_code}"

    # 开始获取判题结果
    start_time = time.time()
    # 循环等待判题结果
    while True:
        # 发送 GET 请求
        judge_result_resp = session.get(JUDGE_RESULT_URL_TEMPLATE.format(submit_id))
        # 发送 GET 请求
        # judge_result_resp = await asyncio.get_event_loop().run_in_executor(None, lambda: session.get(JUDGE_RESULT_URL_TEMPLATE.format(submit_id)))

        if judge_result_resp.status_code == 200:
            # 判题结果
            judge_result_list = judge_result_resp.text.split(",")
            # 判题状态
            judge_status = int(judge_result_list[0])
            # 内存使用
            mem_used = int(judge_result_list[1].split(" ")[0])
            # 执行时间
            exec_time = int(judge_result_list[2].split(" ")[0])

            # 如果判题结束
            # 这里返回True只表示在线判题结束，并不代表答案正确
            # 关于判题结果的进一步处理，在外层函数
            if judge_status in [4, 5, 6, 7, 8, 9, 10, 11]:
                return True, f"{JUDGE_RESULT_DICT[judge_status]}"
            else:
                print(f"🔄 题目 {problem_id} 代码提交成功，正在等待判题结果。当前状态为：{JUDGE_RESULT_DICT[judge_status]}")

        else:
            return False, f"判题结果请求失败，状态码：{judge_result_resp.status_code}"

        # 判断是否超时
        if time.time() - start_time > CONFIG["online_judge_max_time_wait"]:
            return False, "判题超时"

        # 使用异步sleep让出控制权，等待下一轮请求
        await asyncio.sleep(CONFIG["online_judge_poll_interval"])


if __name__ == "__main__":
    # 登录
    session = login_buctoj(CONFIG)

    # 测试problem_id
    problem_id = "0"

    # 读取problem_0.cpp
    code = open(os.path.join(os.path.dirname(__file__), ANSWERS_SAVE_DIR, f"problem_{problem_id}.cpp"), "r",
                encoding="utf-8").read()

    # 在线判题
    online_judge_success, online_judge_result = asyncio.run(online_judge_async(session, problem_id, code))
    if online_judge_success and online_judge_result == "正确":
        print(f"✅ 题目 {problem_id} 在线判题结束，答案正确")
    elif online_judge_success:
        print(f"🔶 题目 {problem_id} 在线判题结束，，答案不正确：{online_judge_result}")
    else:
        print(f"❌ 题目 {problem_id} 在线判题失败，信息: ", online_judge_result)
