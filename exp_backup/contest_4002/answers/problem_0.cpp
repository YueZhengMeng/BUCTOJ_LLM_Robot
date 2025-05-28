/* 代码头注释：说明算法名称和关键技巧 */
// 算法名称：Nim 游戏
// 关键技巧：使用异或和来判断胜负，阿超获胜的条件是阿超的棋子堆的异或和不为零，或者阿喆的棋子堆的异或和为零。

#include <bits/stdc++.h>
using namespace std;
using ll = long long;  // 必须处理大数场景
const int INF = 0x3f3f3f3f;  // 典型竞赛常量定义

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);  // 必须的IO加速

    int n, m;
    cin >> n >> m;

    ll xorA = 0, xorB = 0;
    for (int i = 0; i < n; ++i) {
        ll a;
        cin >> a;
        xorA ^= a;
    }
    for (int i = 0; i < m; ++i) {
        ll b;
        cin >> b;
        xorB ^= b;
    }

    // DEBUG: 输出异或和
    // cout << "xorA: " << xorA << ", xorB: " << xorB << endl;

    if (xorA != 0 || xorB == 0) {  // [FIX] 修改比较条件，正确判断阿超是否有必胜策略
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}