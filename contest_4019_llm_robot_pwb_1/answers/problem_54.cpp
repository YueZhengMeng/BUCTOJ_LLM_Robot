/* 文件头注释：使用C++标准库中的reverse函数实现字符串逆序 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    string str;
    getline(cin, str);  // 读取整行输入，包括空格
    reverse(str.begin(), str.end());  // 使用reverse函数逆序字符串
    cout << str << endl;  // 输出逆序后的字符串
    return 0;
}