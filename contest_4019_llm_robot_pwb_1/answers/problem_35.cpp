/* 文件头注释：字符替换加密算法 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    string input;
    getline(cin, input);  // 读取一行输入

    for (char &c : input) {
        if (c >= 'a' && c < 'z') {
            c += 1;  // 小写字母替换为下一个字母
        } else if (c == 'z') {
            c = 'a';  // 'z'替换为'a'
        } else if (c >= 'A' && c < 'Z') {
            c += 1;  // 大写字母替换为下一个字母
        } else if (c == 'Z') {
            c = 'A';  // 'Z'替换为'A'
        }
        // 其他字符保持不变
    }

    cout << input << endl;  // 输出加密后的字符串
    return 0;
}