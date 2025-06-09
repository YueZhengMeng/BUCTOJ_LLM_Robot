import asyncio
import os

CONFIG = {
    "username": "llm_robot_pwb_1",
    "password": "llm_robot_pwb_072",
    "api_key": os.getenv("DASHSCOPE_API_KEY"),
    "base_url": "https://dashscope.aliyuncs.com/compatible-mode/v1",
    "model_name": "deepseek-v3",
    "verbose": False,
    "only_gen_and_retry": False,
    "prompt_language": "CN",
    "code_generator_prompt_key": "CODE_GENERATOR_CN",
    "fault_locator_prompt_key": "FAULT_LOCATOR_CN",
    "code_repairer_prompt_key": "CODE_REPAIRER_CN",
    "language_id": 1,
    "contest_id": 4020,
    "concurrency_limit": 16,
    "local_test_max_time_wait": 10,
    "submit_code_delay": 10,
    "online_judge_max_time_wait": 15,
    "online_judge_poll_interval": 3,
    "max_local_test_turn": 2,
    "max_online_judge_turn": 2,
    "max_generate_turn": 2,
}

# Robot 19 6
"""
CONFIG["username"] = "19"
CONFIG["password"] = "9CD5CC95E8"
CONFIG["api_key"] = os.getenv("YUNWU_API_KEY")
CONFIG["base_url"] = "https://yunwu.ai/v1"
CONFIG["model_name"] = "o4-mini"
CONFIG["only_gen_and_retry"] = False
CONFIG["prompt_language"] = "EN"
CONFIG["code_generator_prompt_key"] = "CODE_GENERATOR_EN"
CONFIG["fault_locator_prompt_key"] = "FAULT_LOCATOR_EN"
CONFIG["code_repairer_prompt_key"] = "CODE_REPAIRER_EN"
"""

# Robot 20 1,5,6
"""
CONFIG["username"] = "20"
CONFIG["password"] = "BB470A5199"
CONFIG["api_key"] = os.getenv("YUNWU_API_KEY")
CONFIG["base_url"] = "https://yunwu.ai/v1"
CONFIG["model_name"] = "gemini-2.5-pro-preview-05-06"
CONFIG["only_gen_and_retry"] = True
CONFIG["prompt_language"] = "EN"
CONFIG["code_generator_prompt_key"] = "CODE_GENERATOR_EN_SIMPLE"
CONFIG["fault_locator_prompt_key"] = "FAULT_LOCATOR_EN"
CONFIG["code_repairer_prompt_key"] = "CODE_REPAIRER_EN"
"""

# Robot 21 1,2,5,6
"""
CONFIG["username"] = "21"
CONFIG["password"] = "FE95951169"
CONFIG["api_key"] = os.getenv("DASHSCOPE_API_KEY")
CONFIG["base_url"] = "https://dashscope.aliyuncs.com/compatible-mode/v1"
CONFIG["model_name"] = "deepseek-v3"
CONFIG["only_gen_and_retry"] = False
CONFIG["prompt_language"] = "CN"
CONFIG["code_generator_prompt_key"] = "CODE_GENERATOR_CN"
CONFIG["fault_locator_prompt_key"] = "FAULT_LOCATOR_CN"
CONFIG["code_repairer_prompt_key"] = "CODE_REPAIRER_CN"
"""

# os.getenv("DASHSCOPE_API_KEY")
# "https://dashscope.aliyuncs.com/compatible-mode/v1"

BASE_URL = 'https://buctoj.com/'
CSRF_URL = BASE_URL + 'csrf.php'
LOGIN_URL = BASE_URL + 'login.php'
CONTEST_URL_TEMPLATE = BASE_URL + 'contest.php?cid={}'
PROBLEM_URL_TEMPLATE = BASE_URL + 'problem.php?cid={}&pid={}'
SUBMIT_URL = "https://buctoj.com/submit.php"
JUDGE_RESULT_URL_TEMPLATE = "https://buctcoder.com/status-ajax.php?solution_id={}"
JUDGE_RESULT_DICT = ['等待', '等待重判', '编译中', '运行并评判', '正确', '格式错误', '答案错误', '时间超限', '内存超限',
                     '输出超限', '运行错误', '编译错误', '编译成功', '运行完成', '自动评测通过，等待人工确认', '']
#  实验名称
# EXP_NAME = "exp_test"
# 用比赛名称作为实验名称
EXP_NAME = "contest_" + str(CONFIG["contest_id"]) + "_" + CONFIG["username"]
# EXP_NAME = "contest_" + str(CONFIG["contest_id"])
# 获取当前时间，精确到秒
# EXP_NAME = time.strftime("%Y%m%d%H%M%S", time.localtime())

# 创建实验文件夹
EXP_SAVE_DIR = os.path.join(os.path.dirname(__file__), EXP_NAME)
os.makedirs(EXP_SAVE_DIR, exist_ok=True)

# 创建题目保存文件夹
PROBLEM_SAVE_DIR = os.path.join(EXP_SAVE_DIR, "problems")
os.makedirs(PROBLEM_SAVE_DIR, exist_ok=True)

# 创建答案保存文件夹
ANSWERS_SAVE_DIR = os.path.join(EXP_SAVE_DIR, "answers")
os.makedirs(ANSWERS_SAVE_DIR, exist_ok=True)

# 创建聊天历史文件夹
CHAT_HISTORY_SAVE_DIR = os.path.join(EXP_SAVE_DIR, "chat_history")
os.makedirs(CHAT_HISTORY_SAVE_DIR, exist_ok=True)

# 创建聊天历史
CHAT_HISTORY = {
    "code_generator": [],
    "fault_locator": [],
    "code_repairer": []
}

# 创建协程锁
CHAT_HISTORY_LOCK = {
    "code_generator": asyncio.Lock(),
    "fault_locator": asyncio.Lock(),
    "code_repairer": asyncio.Lock()
}
