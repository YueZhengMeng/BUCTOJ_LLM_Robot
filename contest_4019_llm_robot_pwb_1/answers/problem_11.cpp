/* 文件头注释：计算斐波那契数列相邻两项比值的前N项和 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;  // 输入N

    double sum = 0.0;  // 初始化数列和
    double a = 2.0, b = 1.0;  // 初始化斐波那契数列的前两项

    for (int i = 0; i < N; ++i) {
        sum += a / b;  // 计算当前项并累加到和
        double next_a = a + b;  // 计算下一项分子
        double next_b = a;  // 计算下一项分母
        a = next_a;
        b = next_b;
    }

    cout << fixed << setprecision(2) << sum << endl;  // 输出结果，保留两位小数
    return 0;
}