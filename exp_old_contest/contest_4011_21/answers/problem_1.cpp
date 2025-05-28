/* 文件头注释：十六进制字符流转换为字符串 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    string input;
    getline(cin, input); // 读取整行输入
    stringstream ss(input);
    string hexCode;
    string result;

    // 逐个读取十六进制代码并转换为字符
    while (ss >> hexCode) {
        // 将十六进制字符串转换为整数
        int asciiCode = stoi(hexCode, nullptr, 16);
        // 将整数转换为对应的ASCII字符
        char ch = static_cast<char>(asciiCode);
        result += ch;
    }

    // 输出结果
    cout << result << endl;
    return 0;
}