/* 文件头注释：字符串连接，使用std::string的+运算符 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    string str1, str2;
    // 读取两个字符串
    getline(cin, str1);
    getline(cin, str2);
    // 连接字符串
    string result = str1 + str2;
    // 输出结果
    cout << result << endl;
    return 0;
}