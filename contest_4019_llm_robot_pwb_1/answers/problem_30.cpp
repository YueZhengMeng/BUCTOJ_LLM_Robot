/* 文件头注释：使用带参宏计算两个整数相除的余数 */
#include <bits/stdc++.h>
using namespace std;

// 定义带参宏来计算余数
#define MOD(a, b) ((a) % (b))

int main() {
    int a, b;
    // 输入两个整数
    cin >> a >> b;
    // 输出a除以b的余数
    cout << MOD(a, b) << endl;
    return 0;
}