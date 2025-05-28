/* 文件头注释：计算所有点对的距离平方和，并按照题目要求进行模运算 */
#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int main() {
    int N;
    cin >> N;
    long long sum_x = 0, sum_y = 0, sum_x2 = 0, sum_y2 = 0;
    
    for (int i = 0; i < N; ++i) {
        long long x, y;
        cin >> x >> y;
        sum_x = (sum_x + x) % MOD;
        sum_y = (sum_y + y) % MOD;
        sum_x2 = (sum_x2 + x * x) % MOD;
        sum_y2 = (sum_y2 + y * y) % MOD;
    }
    
    // 计算距离平方和：2N * (sum_x2 + sum_y2) - 2 * (sum_x^2 + sum_y^2)
    long long result = (2 * N % MOD * (sum_x2 + sum_y2) % MOD - 2 * (sum_x * sum_x % MOD + sum_y * sum_y % MOD) % MOD + MOD) % MOD;
    
    cout << result << endl;
    return 0;
}