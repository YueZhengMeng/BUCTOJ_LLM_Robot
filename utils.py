import json
import os
import re
import shutil

import requests

from config import CONFIG, BASE_URL, CSRF_URL, LOGIN_URL, PROBLEM_SAVE_DIR


def login_buctoj(config):
    """登录函数，返回已登录的 session"""
    print("⏳ 开始登录BUCTOJ")
    #  加载用户名和密码
    username, password = config["username"], config["password"]

    # 创建会话
    session = requests.Session()

    # 获取 CSRF token
    csrf_resp = session.get(CSRF_URL)
    csrf_token = csrf_resp.text.strip()
    print("✅ 获取到 CSRF token:", csrf_token)

    # 构造登录请求
    payload = {"user_id": username, "password": password, "csrf": csrf_token, "submit": ""}

    # 登录
    session.post(LOGIN_URL, data=payload)

    # 验证是否登录成功
    home = session.get(BASE_URL)
    if username in home.text:
        print(f"✅ 登录成功：{username}")
        return session
    else:
        raise Exception("❌ 登录失败，请检查用户名密码或CSRF token是否正确")


def prepare_save_dir(dir_path):
    # 清空目录下的所有内容
    for filename in os.listdir(dir_path):
        file_path = os.path.join(dir_path, filename)
        try:
            if os.path.isfile(file_path) or os.path.islink(file_path):
                os.unlink(file_path)
            elif os.path.isdir(file_path):
                shutil.rmtree(file_path)
        except Exception as e:
            print(f'删除 {file_path} 失败: {e}')


def match_cpp_code(code_generate_result):
    """匹配 C++ 代码"""
    # 使用正则表达式，匹配```cpp```包裹的代码，匹配成功的结果可能有多个，保留最长的那一个
    # 使用findall直接获取所有代码块
    cpp_code_blocks = re.findall(
        r'^```cpp\s*(.*?)\s*```$',  # 严格匹配代码块边界
        code_generate_result,
        re.DOTALL | re.MULTILINE  # 同时支持跨行和跨段落匹配
    )

    if cpp_code_blocks:
        # 选择最长的代码块（按字符长度比较）
        cpp_code_match = max(cpp_code_blocks, key=lambda x: len(x.strip()))
    else:
        cpp_code_match = None

    if cpp_code_match:
        return cpp_code_match.strip()
    else:
        return None


def load_problems():
    problems = []
    filenames = os.listdir(PROBLEM_SAVE_DIR)
    for filename in filenames:
        if filename.endswith(".json"):
            filepath = os.path.join(PROBLEM_SAVE_DIR, filename)
            with open(filepath, "r", encoding="utf-8") as f:
                problem = json.load(f)
                problems.append(problem)
    # 按照pid升序排序
    problems.sort(key=lambda x: x["idx"])
    return problems


if __name__ == "__main__":
    session = login_buctoj(CONFIG)
    print(session.cookies)
