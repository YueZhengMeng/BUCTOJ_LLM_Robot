/* 文件头注释：本题通过将整数转换为字符串来简化位数统计、逐位输出和逆序输出 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    string num;
    cin >> num;  // 读取输入的数字字符串

    // 第一行输出位数
    cout << num.length() << endl;

    // 第二行逐位输出数字，用空格分隔
    for (int i = 0; i < num.length(); ++i) {
        if (i > 0) cout << " ";
        cout << num[i];
    }
    cout << endl;

    // 第三行逆序输出数字
    for (int i = num.length() - 1; i >= 0; --i) {
        cout << num[i];
    }
    cout << endl;

    return 0;
}