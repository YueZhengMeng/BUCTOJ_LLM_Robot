import asyncio
import hashlib
import json
import os

from config import CHAT_HISTORY_SAVE_DIR, CHAT_HISTORY, CHAT_HISTORY_LOCK


async def save_chat_history_async(agent_name, messages):
    """
    保存聊天历史
    """
    if not messages:
        return  # 空消息列表无需处理

    # 检查 agent_name 是否存在于 CHAT_HISTORY 中
    if agent_name not in CHAT_HISTORY:
        CHAT_HISTORY[agent_name] = []

    # 使用稳定哈希算法，如 sha256
    hash_value = hashlib.sha256(messages[0]["content"].encode("utf-8")).hexdigest()
    """
    # 该缓存与查找功能已废弃
    # 查找是否已经存在相同的哈希值
    found = False
    for i in range(len(CHAT_HISTORY[agent_name])):
        if CHAT_HISTORY[agent_name][i]["hash"] == hash_value:
            CHAT_HISTORY[agent_name][i]["messages"] = messages
            found = True
            break

    if not found:
        # 将哈希值和消息列表添加到 CHAT_HISTORY 中
        CHAT_HISTORY[agent_name].append({"hash": hash_value, "messages": messages})
    """
    # 将哈希值和消息列表添加到 CHAT_HISTORY 中
    CHAT_HISTORY[agent_name].append({"hash": hash_value, "messages": messages})

    # 打开智能体专属的聊天历史文件，写入JSON
    agent_chat_history_path = os.path.join(CHAT_HISTORY_SAVE_DIR, f"{agent_name}.json")
    async with CHAT_HISTORY_LOCK["code_generator"]:
        with open(agent_chat_history_path, "w", encoding="utf-8") as f:
            json.dump(CHAT_HISTORY[agent_name], f, ensure_ascii=False, indent=4)


if __name__ == "__main__":
    # 测试保存
    messages = [
        {"role": "user", "content": "What is the capital of France?"}
    ]
    asyncio.run(save_chat_history_async("code_generator", messages))
    # 测试同一次对话增量保存
    messages = [
        {"role": "user", "content": "What is the capital of France?"},
        {"role": "assistant", "content": "Paris is the capital of France."}
    ]
    asyncio.run(save_chat_history_async("code_generator", messages))
    # 测试不同次对话增量保存
    messages = [
        {"role": "user", "content": "法国的首都是哪里？"},
        {"role": "assistant", "content": "法兰的首都是巴黎。"}
    ]
    asyncio.run(save_chat_history_async("code_generator", messages))
