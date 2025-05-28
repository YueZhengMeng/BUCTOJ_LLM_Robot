from chat_history_handler_async import save_chat_history_async
from config import CONFIG
from llm_api_async import openai_complete_async
from prompts import PROMPTS, concat_fault_locate_context


async def fault_locator_async(problem, buggy_code, error_context, prompt_key=CONFIG["fault_locator_prompt_key"]):
    # 拼接prompt
    fault_locator_prompt = concat_fault_locate_context(PROMPTS[prompt_key], problem, buggy_code, error_context)
    # 组装message
    fault_locator_massages = [
        {"role": "user", "content": fault_locator_prompt}
    ]
    # 调用openai
    fault_locator_massages = await openai_complete_async(fault_locator_massages)
    # 保存对话记录
    await save_chat_history_async("fault_locator", fault_locator_massages)
    # 代码故障定位与纠错建议
    fault_locator_advise = fault_locator_massages[-1]["content"]
    # 代码故障定位与纠错建议 和 对话记录
    return fault_locator_advise, fault_locator_massages
