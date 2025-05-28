#include <iostream>
#include <string>
#include <vector> // 虽然在这个特定解法中未使用，但通常在CP中是标准包含
#include <algorithm> // 同样，对于某些解法可能有用

int main() {
    // 优化C++标准输入输出流，在竞技编程中常见
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n; // 读取输入的整数

    // 将整数转换为字符串
    std::string s_n = std::to_string(n);
    
    std::string result = ""; // 用于存储最终的魔法阵图案字符串

    // 遍历字符串中的每个字符（即原始数字的每一位）
    for (char c : s_n) {
        // 将字符数字转换为整数数字
        // 例如 '5' - '0' 得到整数 5
        int digit = c - '0'; 
        
        // 判断数字的奇偶性
        if (digit % 2 == 0) { // 如果是偶数
            result += '*';    // 追加 '*'
        } else {              // 如果是奇数
            result += '#';    // 追加 '#'
        }
    }

    std::cout << result << std::endl; // 输出结果字符串

    return 0; // 程序成功结束
}