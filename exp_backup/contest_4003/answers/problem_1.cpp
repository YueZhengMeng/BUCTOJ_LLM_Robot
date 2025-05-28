/* 代码头注释：消失的账单 - 数学推导法 */
// 核心技巧：通过方程求解，直接计算 A, B, C 的值，避免枚举。
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;

    // 方程1：A + B + C = n
    // 方程2：1000B + 2500C = m
    // 通过方程2，可以解出 B = (m - 2500C) / 1000
    // 代入方程1，得到 A = n - B - C

    // 遍历 C 的可能值，计算 B 和 A
    // 由于 B 必须为非负整数，C 的最大值为 min(n, m / 2500)
    ll maxC = min(n, m / 2500);
    vector<tuple<ll, ll, ll>> solutions; // 记录所有满足条件的解
    for (ll C = 0; C <= maxC; ++C) {
        ll remaining = m - 2500 * C;
        if (remaining < 0) continue; // 无解
        if (remaining % 1000 != 0) continue; // B 必须为整数
        ll B = remaining / 1000;
        ll A = n - B - C;
        if (A >= 0 && B >= 0) {
            solutions.emplace_back(A, B, C);
        }
    }

    // 选择最优解：优先选择 A 最大的解
    if (!solutions.empty()) {
        auto [A, B, C] = *max_element(solutions.begin(), solutions.end(), [](const tuple<ll, ll, ll>& a, const tuple<ll, ll, ll>& b) {
            return get<0>(a) < get<0>(b);
        });
        cout << A << " " << B << " " << C << "\n";
    } else {
        // 无解情况
        cout << "-1\n";
    }

    return 0;
}