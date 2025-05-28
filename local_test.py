import os
import subprocess
import time

from config import CONFIG


def compile_cpp(cpp_file_path, exe_file_path=None):
    """
    编译C++源代码
    """
    # 确保源文件存在
    if not os.path.exists(cpp_file_path):
        return False, None, f"源文件{cpp_file_path}不存在"

    # 构建输出路径
    # 如果没有给出exe_file_path，则使用cpp_file_path更换后缀作为exe_file_path
    exe_file_path = exe_file_path or cpp_file_path.replace(".cpp", ".exe")

    # 构建编译命令
    compile_cmd = ["g++", cpp_file_path, "-o", exe_file_path, "-std=c++11"]

    # 多进程执行编译命令
    # 设置check=False，编译失败也不会抛出异常，继续执行后续代码，便于后续拿到报错信息
    try:
        compile_process = subprocess.run(compile_cmd, capture_output=True, text=True, check=False)
    except Exception as e:
        # 报错信息太长，只截取前500个字符
        return False, None, f"编译时发生异常: {str(e)[:500]}"

    # 如果编译失败，则返回False和错误信息
    # 报错信息太长，只截取前500个字符。报错信息可能为None，所以需要条件赋值。
    if compile_process.returncode != 0:
        return False, None, f"编译失败: {compile_process.stderr[:500] if compile_process.stderr else ''}"

    # 编译成功，返回成功标志、输出路径和错误信息
    return True, exe_file_path, ""


def run_cpp(exe_file_path, input_data=None, timeout=CONFIG["local_test_max_time_wait"]):
    """
    运行已编译的C++程序

    参数:
        exe_file_path: 可执行文件路径
        input_data: 输入数据(字符串或列表)
        timeout: 运行超时时间(秒)

    返回:
        (success: bool, output: str, error: str, execution_time: float)
    """
    # 准备输入数据
    input_str = ""
    if input_data is not None:
        if isinstance(input_data, list):
            input_str = "\n".join(map(str, input_data)) + "\n"
        else:
            input_str = str(input_data) + "\n"

    try:
        start_time = time.time()
        run_process = subprocess.run(exe_file_path, input=input_str, timeout=timeout, capture_output=True, text=True,
                                     check=False)
        execution_time = time.time() - start_time

        # 如果运行失败，则返回False和错误信息
        # 报错信息太长，只截取前500个字符。报错信息可能为None，所以需要条件赋值。
        if run_process.returncode != 0:
            return False, "", f"运行时发生错误: {run_process.stderr[:500] if run_process.stderr else ''}", execution_time

        return True, run_process.stdout, "", execution_time

    except subprocess.TimeoutExpired:
        return False, "", f"程序执行超时(>{timeout}秒)", float(timeout)
    except (OSError, subprocess.SubprocessError) as e:
        # 报错信息太长，只截取前500个字符
        return False, "", f"运行时发生异常: {str(e)[:500]}", 0.0


def local_test(cpp_file_path, sample_input, sample_output):
    # 编译cpp文件
    compile_success, exe_file_path, compile_error = compile_cpp(cpp_file_path)
    if not compile_success:
        return False, compile_error
    # 运行exe文件
    run_success, run_output, run_error, exec_time = run_cpp(exe_file_path, sample_input)
    if not run_success:
        print(f"运行失败: {run_error}")
        return False, run_error

    # 确保输出不是 None，并转换为字符串
    run_output = str(run_output) if run_output is not None else ""
    sample_output = str(sample_output) if sample_output is not None else ""

    # 判断运行结果是否一致时，要去掉多余换行符
    # run_output与sample_output都可能有多行，需要逐行strip后比较
    run_lines = [line.strip() for line in run_output.splitlines()]
    sample_lines = [line.strip() for line in sample_output.splitlines()]

    # 判断结果一致
    if run_lines == sample_lines:
        return True, ""
    else:
        # 向LLM反馈错误信息时，保留原始结果
        # 有些输出死循环的bug程序，run_output会很长，这里需要截取前500个字符
        return False, f"样例输入\n{sample_input}\n实际运行结果：\n{run_output[:500]}\n与预期的样例输出\n{sample_output}\n不一致"


# 使用示例
if __name__ == "__main__":
    test_problem_id = 0
    # 这是个简单的 a+b 程序
    test_cpp_file_path = f"./exp_test/problem_{test_problem_id}.cpp"
    test_sample_input = "1 3"
    test_sample_output = "4"
    local_test_success, local_test_error = local_test(test_cpp_file_path, test_sample_input,
                                                      test_sample_output)
    if local_test_success:
        print(f"✅ 题目 {test_problem_id} 本地测试通过")
    else:
        print(f"❌ 题目 {test_problem_id} 本地测试失败，信息: ", local_test_error)
