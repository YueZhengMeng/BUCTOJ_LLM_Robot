import asyncio
import os

CONFIG = {
    "username": "2025200823",  # BUCTOJ的用户名，换成你自己的。
    "password": "Pp072075408",  # 密码，换成你自己的。
    "contest_id": 4312,  # BUCTOJ比赛的ID，这里填你要参加的比赛ID。浏览器打开后比赛页面后，地址栏中会显示。
    "api_key": os.getenv("DEEPSEEK_API_KEY"),  # LLM厂商平台提供的API Key，我在这里用的是Deepseek官网的。
    "base_url": "https://api.deepseek.com/v1",  # LLM厂商API平台的URL，我这里用的是Deepseek官网的。
    "model_name": "deepseek-reasoner",  # LLM厂商API平台的模型名称，我这里用的是deepseek-v3.2-think。
    "verbose": False,  # 本来想做一个调试模式，实时输出日志，但是没做完。该功能无效，不用在意。
    "only_gen_and_retry": True,  # 只生成代码，如果评测不通过，直接重新生成，不进行故障定位和修复。
    "prompt_language": "EN",  # Prompt模板的语言，可选值：CN, EN
    "code_generator_prompt_key": "CODE_GENERATOR_EN",
    # 代码生成智能体的Prompt模板，其他可选项：CODE_GENERATOR_EN、CODE_GENERATOR_CN_SIMPLE、CODE_GENERATOR_EN_SIMPLE
    "fault_locator_prompt_key": "FAULT_LOCATOR_EN",  # 故障定位智能体的Prompt模板，其他可选项：FAULT_LOCATOR_EN
    "code_repairer_prompt_key": "CODE_REPAIRER_EN",  # 代码修复智能体的Prompt模板，其他可选项：CODE_REPAIRER_EN
    "language_id": 1,  # BUCTOJ平台的编程语言代号，1表示C++。不用改。
    "concurrency_limit": 16,  # LLM API Call的最大协程并发数，不要太大。
    "local_test_max_time_wait": 10,  # 本地测试最长运行时间，超过这个时间，就认为本地测试超时。
    "submit_code_delay": 10,  # BUCTOJ平台同一个账号提交代码的最短间隔时间为10秒。不用改。
    "online_judge_max_time_wait": 15,  # BUCTOJ在线判题最长等待时间，超过这个时间，就认为在线判题超时。
    "online_judge_poll_interval": 3,  # 向BUCTOJ平台轮询在线判题结果的间隔时间，默认为3秒。不用改。
    "max_local_test_turn": 2,  # 本地测试的最多尝试次数，超过这个次数就放弃。
    "max_online_judge_turn": 2,  # 在线判题的最多尝试次数，超过这个次数就放弃。
    "max_generate_turn": 2,  # 重复生成代码的最多尝试次数，超过这个次数就放弃。
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

"""
"username": "llm_robot_pwb_1",
"password": "llm_robot_pwb_072",
"""

"""
"username": "YueZhengMeng",
"password": "Pp072075408",
"""

"""
"username": "2025200823",
"password": "Pp072075408",
"""

# BUCTOJ平台的重要接口
BASE_URL = 'https://buctoj.com/'
CSRF_URL = BASE_URL + 'csrf.php'
LOGIN_URL = BASE_URL + 'login.php'
CONTEST_URL_TEMPLATE = BASE_URL + 'contest.php?cid={}'
PROBLEM_URL_TEMPLATE = BASE_URL + 'problem.php?cid={}&pid={}'
SUBMIT_URL = "https://buctoj.com/submit.php"
JUDGE_RESULT_URL_TEMPLATE = "https://buctcoder.com/status-ajax.php?solution_id={}"
# BUCTOJ平台返回的评测结果ID与含义的对照表
JUDGE_RESULT_DICT = ['等待', '等待重判', '编译中', '运行并评判', '正确', '格式错误', '答案错误', '时间超限', '内存超限',
                     '输出超限', '运行错误', '编译错误', '编译成功', '运行完成', '自动评测通过，等待人工确认', '']

# 实验名称，也是日志和结果文件的保存地址
# 重要，记得修改，别弄混淆了
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
# 这些协程互斥锁是为了保证同时只有一个协程修改保存聊天历史记录的文件
# 不是LLM API Call并发数控制
CHAT_HISTORY_LOCK = {
    "code_generator": asyncio.Lock(),
    "fault_locator": asyncio.Lock(),
    "code_repairer": asyncio.Lock()
}
