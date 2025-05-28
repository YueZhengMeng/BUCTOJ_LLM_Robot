from openai import OpenAI

from config import CONFIG


def openai_complete(messages):
    try:
        client = OpenAI(
            api_key=CONFIG["api_key"],
            base_url=CONFIG["base_url"],
        )
        # 查看有哪些模型可以调用
        # print(client.models.list())
        completion = client.chat.completions.create(
            model=CONFIG["model_name"],
            messages=messages,
        )
        messages.append({"role": "assistant", "content": completion.choices[0].message.content})
        return messages
    except Exception as e:
        print(e)
        messages.append({"role": "assistant", "content": "Request Error"})
        return messages


if __name__ == "__main__":
    messages = [
        {"role": "system", "content": "You are a helpful assistant."},
        {"role": "user", "content": "Who won the world series in 2020?"},
        {"role": "assistant", "content": "The Los Angeles Dodgers won the World Series in 2020."},
        {"role": "user", "content": "Where was it played?"}
    ]
    messages = openai_complete(messages)
    content = messages[-1]["content"]
    print(content)
