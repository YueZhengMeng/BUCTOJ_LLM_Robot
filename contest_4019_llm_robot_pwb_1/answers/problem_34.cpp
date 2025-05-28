/* 文件头注释：使用函数和带参的宏从三个数中找出最大的数 */
#include <bits/stdc++.h>
using namespace std;

// 函数实现：返回三个数中的最大值
double maxOfThree(double a, double b, double c) {
    return max(max(a, b), c);
}

// 带参的宏实现：返回三个数中的最大值
#define MAX_OF_THREE(a, b, c) ((a) > (b) ? ((a) > (c) ? (a) : (c)) : ((b) > (c) ? (b) : (c)))

int main() {
    double a, b, c;
    cin >> a >> b >> c;

    // 使用函数找出最大值并输出
    double maxFunc = maxOfThree(a, b, c);
    printf("%.3f\n", maxFunc);

    // 使用宏找出最大值并输出
    double maxMacro = MAX_OF_THREE(a, b, c);
    printf("%.3f\n", maxMacro);

    return 0;
}