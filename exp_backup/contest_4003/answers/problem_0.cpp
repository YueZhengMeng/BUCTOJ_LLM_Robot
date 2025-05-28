/* 代码头注释：说明算法名称和关键技巧 */
// 算法名称：博弈论 - Nim游戏
// 关键技巧：计算阿超和阿喆所有堆的异或和，比较两者大小

#include <bits/stdc++.h>
using namespace std;
using ll = long long;  // 必须处理大数场景
const int INF = 0x3f3f3f3f;  // 典型竞赛常量定义

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);  // 必须的IO加速

    int n, m;
    cin >> n >> m;

    // 读取阿超的棋子堆数
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // 读取阿喆的棋子堆数
    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }

    // 计算阿超所有堆的异或和
    ll xor_a = 0;
    for (int i = 0; i < n; ++i) {
        xor_a ^= a[i];
    }

    // 计算阿喆所有堆的异或和
    ll xor_b = 0;
    for (int i = 0; i < m; ++i) {
        xor_b ^= b[i];
    }

    // [FIX] 判断阿超是否有必胜策略
    if ((xor_a != 0 && xor_b == 0) || (xor_a > xor_b)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}