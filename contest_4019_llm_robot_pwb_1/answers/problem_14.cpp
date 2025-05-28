/* 文件头注释：使用牛顿迭代法计算平方根 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    double a;
    cin >> a;

    // 初始猜测值，通常选择a/2
    double x0 = a / 2.0;
    double x1 = 0.0;

    // 迭代直到满足精度要求
    while (true) {
        x1 = 0.5 * (x0 + a / x0);
        if (fabs(x1 - x0) < 0.00001) {
            break;
        }
        x0 = x1;
    }

    // 输出保留3位小数
    cout << fixed << setprecision(3) << x1 << endl;

    return 0;
}