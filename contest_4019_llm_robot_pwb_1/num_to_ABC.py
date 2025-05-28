def number_to_letters(n):
    result = ""
    while n >= 0:
        remainder = n % 26
        result = chr(ord('A') + remainder) + result
        n = n // 26 - 1
        if n < 0:
            break
    return result

# 生成0-100的映射
mapping = {i: number_to_letters(i) for i in range(101)}

# 打印结果
for num, letters in mapping.items():
    print(f"{num}: {letters}")