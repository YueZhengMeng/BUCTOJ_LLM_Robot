/* 代码头注释：矩阵快速幂法计算斐波那契数列第n项，时间复杂度O(log n) */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 10000;  // 结果取模的值

// 定义2x2矩阵
struct Matrix {
    ll a[2][2];
    Matrix() { memset(a, 0, sizeof(a)); }
    Matrix operator*(const Matrix& other) const {
        Matrix res;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    res.a[i][j] = (res.a[i][j] + a[i][k] * other.a[k][j]) % MOD;
                }
            }
        }
        return res;
    }
};

// 矩阵快速幂
Matrix matrix_pow(Matrix base, ll power) {
    Matrix result;
    result.a[0][0] = result.a[1][1] = 1;  // 单位矩阵
    while (power > 0) {
        if (power & 1) {
            result = result * base;
        }
        base = base * base;
        power >>= 1;
    }
    return result;
}

// 计算斐波那契数列第n项
ll fibonacci(ll n) {
    if (n == 0) return 0;
    Matrix base;
    base.a[0][0] = base.a[0][1] = base.a[1][0] = 1;
    Matrix result = matrix_pow(base, n - 1);
    return result.a[0][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n;
    while (cin >> n && n != -1) {
        cout << fibonacci(n) << '\n';
    }
    return 0;
}