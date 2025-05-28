/* 代码头注释：完全背包问题 - 动态规划解法
   关键技巧：使用一维数组优化空间复杂度，内层循环正向遍历以实现完全背包特性 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, W;
    cin >> n;
    vector<int> w(n), v(n);
    for (int i = 0; i < n; ++i) {
        cin >> w[i] >> v[i];
    }
    cin >> W;

    vector<int> dp(W + 1, 0);  // dp[j]表示容量为j时的最大价值

    for (int i = 0; i < n; ++i) {
        for (int j = w[i]; j <= W; ++j) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);  // 状态转移方程
        }
    }

    cout << dp[W] << endl;  // 输出最大价值

    return 0;
}