/* 文件头注释：使用C++的substr函数提取子串 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    string s;
    
    // 输入字符串长度n
    cin >> n;
    // 输入字符串s
    cin >> s;
    // 输入起始位置m
    cin >> m;
    
    // 检查m是否合法
    if (m < 1 || m > n) {
        cout << "Invalid m value" << endl;
        return 0;
    }
    
    // 提取从第m个字符开始的子串（注意C++中字符串索引从0开始）
    string substring = s.substr(m - 1);
    
    // 输出子串
    cout << substring << endl;
    
    return 0;
}