/* 文件头注释：使用C++标准库中的reverse函数实现字符串逆序 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    getline(cin, s);  // 读取一行输入
    reverse(s.begin(), s.end());  // 反转字符串
    cout << s << endl;  // 输出反转后的字符串
    return 0;
}