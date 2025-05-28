/* 文件头注释：镜像文字处理 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    while (cin >> s) {
        string mirrored = s; // 初始化为原字符串
        // 添加逆序字符串（从倒数第二个字符开始）
        for (int i = s.length() - 2; i >= 0; --i) {
            mirrored += s[i];
        }
        cout << mirrored << endl;
    }
    return 0;
}