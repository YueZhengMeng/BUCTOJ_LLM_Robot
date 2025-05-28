from chat_history_handler import save_chat_history
from config import CONFIG
from llm_api import openai_complete
from prompts import PROMPTS, concat_fault_locate_context


def fault_locator(problem, buggy_code, error_context, prompt_key=CONFIG["fault_locator_prompt_key"]):
    # 拼接prompt
    fault_locator_prompt = concat_fault_locate_context(PROMPTS[prompt_key], problem, buggy_code, error_context)
    # 组装message
    fault_locator_massages = [
        {"role": "user", "content": fault_locator_prompt}
    ]
    # 调用openai
    fault_locator_massages = openai_complete(fault_locator_massages)
    # 保存对话记录
    save_chat_history("fault_locator", fault_locator_massages)
    # 代码故障定位与纠错建议
    fault_locator_advise = fault_locator_massages[-1]["content"]
    # 代码故障定位与纠错建议 和 对话记录
    return fault_locator_advise, fault_locator_massages
