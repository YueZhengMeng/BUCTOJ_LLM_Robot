/* 文件头注释：计算第12个月的兔子对数，使用迭代方法实现斐波那契数列 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 12; // 计算12个月后的兔子对数
    int a = 1, b = 1; // 初始化前两个月的兔子对数
    for (int i = 3; i <= n; ++i) {
        int c = a + b; // 计算当前月的兔子对数
        a = b; // 更新前一个月的值
        b = c; // 更新当前月的值
    }
    cout << b << endl; // 输出第12个月的兔子对数
    return 0;
}