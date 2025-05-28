from chat_history_handler import save_chat_history
from config import CONFIG
from llm_api import openai_complete
from prompts import PROMPTS, concat_code_repairer_context
from utils import match_cpp_code


def code_repairer(problem, buggy_code, error_context, fault_locate_result,
                  prompt_key=CONFIG["code_repairer_prompt_key"]):
    # 拼接prompt
    code_repairer_prompt = concat_code_repairer_context(PROMPTS[prompt_key], problem, buggy_code, error_context,
                                                        fault_locate_result)
    # 组装message
    code_repairer_messages = [
        {"role": "user", "content": code_repairer_prompt}
    ]
    # 调用openai
    code_repairer_messages = openai_complete(code_repairer_messages)
    # 保存对话记录
    save_chat_history("code_repairer", code_repairer_messages)
    # 代码生成结果
    code = match_cpp_code(code_repairer_messages[-1]["content"])
    # 返回代码和对话记录
    return code, code_repairer_messages
