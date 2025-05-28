/* 文件头注释：计算1~a的和、1~b的平方和、1~c的倒数和，并保留两位小数 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;

    // 计算1~a的和
    int sum_a = 0;
    for (int i = 1; i <= a; ++i) {
        sum_a += i;
    }

    // 计算1~b的平方和
    int sum_b_square = 0;
    for (int i = 1; i <= b; ++i) {
        sum_b_square += i * i;
    }

    // 计算1~c的倒数和
    double sum_c_reciprocal = 0.0;
    for (int i = 1; i <= c; ++i) {
        sum_c_reciprocal += 1.0 / i;
    }

    // 计算总和并保留两位小数
    double total = sum_a + sum_b_square + sum_c_reciprocal;
    cout << fixed << setprecision(2) << total << endl;

    return 0;
}