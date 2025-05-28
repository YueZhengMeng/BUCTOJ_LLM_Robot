/* 文件头注释：使用标准库的sort函数对三个字符串进行排序 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    // 定义三个字符串变量
    string str1, str2, str3;
    
    // 读取三个字符串
    getline(cin, str1);
    getline(cin, str2);
    getline(cin, str3);
    
    // 将字符串放入vector中以便排序
    vector<string> strs = {str1, str2, str3};
    
    // 使用sort函数对字符串进行排序
    sort(strs.begin(), strs.end());
    
    // 输出排序后的字符串
    for (const string& s : strs) {
        cout << s << endl;
    }
    
    return 0;
}