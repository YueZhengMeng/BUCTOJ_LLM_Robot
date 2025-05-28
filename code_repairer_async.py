from chat_history_handler_async import save_chat_history_async
from config import CONFIG
from llm_api_async import openai_complete_async
from prompts import PROMPTS, concat_code_repairer_context
from utils import match_cpp_code


async def code_repairer_async(problem, buggy_code, error_context, fault_locate_result,
                              prompt_key=CONFIG["code_repairer_prompt_key"]):
    # 拼接prompt
    code_repairer_prompt = concat_code_repairer_context(PROMPTS[prompt_key], problem, buggy_code, error_context,
                                                        fault_locate_result)
    # 组装message
    code_repairer_messages = [
        {"role": "user", "content": code_repairer_prompt}
    ]
    # 调用openai
    code_repairer_messages = await openai_complete_async(code_repairer_messages)
    # 保存对话记录
    await save_chat_history_async("code_repairer", code_repairer_messages)
    # 代码生成结果
    code = match_cpp_code(code_repairer_messages[-1]["content"])
    # 返回代码和对话记录
    return code, code_repairer_messages
