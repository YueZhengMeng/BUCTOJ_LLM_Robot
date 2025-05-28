/* 代码头注释：最短Hamilton路径 - 动态规划 + 状态压缩 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }

    // DP状态：dp[mask][u] 表示在状态mask下，当前在点u的最短路径
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));
    dp[1][0] = 0;  // 初始状态：只访问过起点0

    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int u = 0; u < n; ++u) {
            if (!(mask & (1 << u))) continue;  // 当前状态未访问过u
            for (int v = 0; v < n; ++v) {
                if (mask & (1 << v)) continue;  // 已经访问过v
                dp[mask | (1 << v)][v] = min(dp[mask | (1 << v)][v], dp[mask][u] + a[u][v]);
            }
        }
    }

    // 最终状态：所有点都访问过，且当前在终点n-1
    cout << dp[(1 << n) - 1][n - 1] << endl;

    return 0;
}