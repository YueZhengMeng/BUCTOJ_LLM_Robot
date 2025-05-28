/* 代码头注释：说明算法名称和关键技巧 */
// 算法名称：数学推导法
// 关键技巧：通过方程求解，直接计算 C 的范围，然后确定 B 和 A

#include <bits/stdc++.h>
using namespace std;
using ll = long long;  // 必须处理大数场景
const int INF = 0x3f3f3f3f;  // 典型竞赛常量定义

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);  // 必须的IO加速

    ll n, m;
    cin >> n >> m;

    // 根据方程 A + B + C = n 和 1000B + 2500C = m
    // 可以推导出 1000B + 2500C = m
    // 并且 A + B + C = n

    // 枚举 C 的所有可能值
    for (ll C = 0; C <= n; ++C) {
        ll remaining = m - 2500 * C;
        if (remaining < 0) continue;  // 如果剩余费用为负，跳过

        if (remaining % 1000 != 0) continue;  // 如果剩余费用不能被 1000 整除，跳过

        ll B = remaining / 1000;
        if (B < 0 || B > n) continue;  // 如果 B 不在合理范围内，跳过

        ll A = n - B - C;
        if (A < 0 || A > n) continue;  // 如果 A 不在合理范围内，跳过

        // [FIX] 确保 A, B, C 都是非负整数且总和为 n
        if (A >= 0 && B >= 0 && C >= 0 && A + B + C == n) {
            // 如果所有条件都满足，输出结果
            cout << A << " " << B << " " << C << endl;
            return 0;
        }
    }

    // 如果没有找到合适的解，输出 -1
    cout << -1 << endl;

    return 0;
}