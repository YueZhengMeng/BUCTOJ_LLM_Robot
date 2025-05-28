from chat_history_handler import save_chat_history
from config import CONFIG
from llm_api import openai_complete
from prompts import PROMPTS, concat_problem_context
from utils import match_cpp_code


def code_generator(problem, prompt_key=CONFIG["code_generator_prompt_key"]):
    # 拼接prompt
    code_generate_prompt = concat_problem_context(PROMPTS[prompt_key], problem)
    # 组装message
    code_generate_messages = [
        {"role": "user", "content": code_generate_prompt}
    ]
    # 调用openai
    code_generate_messages = openai_complete(code_generate_messages)
    # 保存对话记录
    save_chat_history("code_generator", code_generate_messages)
    # 代码生成结果
    code = match_cpp_code(code_generate_messages[-1]["content"])
    # 返回代码和对话记录
    return code, code_generate_messages


if __name__ == "__main__":
    test_problem = {
        "idx": 0,
        "title": "问题 A: 121",
        "description": "定义一个字符串 $S_n$，其定义为：\r\n$$\r\nS_n = \\begin{cases} \r\n1 & \\text{若 } n = 1, \\\\\r\nS_{n-1} + \\overline{n} + S_{n-1} & \\text{若 } n > 1.\r\n\\end{cases}\r\n$$\r\n其中，$\\overline{n}$ 表示数字 $n$ 对应的字符串。给定一个整数 $n$，请输出 $S_n$ 。\n\n说明：这里的 $+$ 表示字符串连接，$\\overline{n}$ 表示将数字 $n$ 转换为字符串形式。例如，当 $n=2$ 时，$\\overline{n}$ 为 \"2\" 。",
        "input_description": "输入一行，包含一个整数 $n\\ (1 \\leq n \\leq 9)$ 。",
        "sample_input": "3",
        "output_description": "输出 $S_n$ 。",
        "sample_output": "1213121",
        "hint": "未找到"
    }
    print(code_generator(test_problem))
