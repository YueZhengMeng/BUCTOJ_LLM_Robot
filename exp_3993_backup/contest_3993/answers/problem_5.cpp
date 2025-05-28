/* 石子合并问题 - 区间动态规划
 * 核心技巧：使用前缀和快速计算区间和，枚举所有可能的合并点
 * 时间复杂度：O(n^3)
 * 空间复杂度：O(n^2)
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // 前缀和数组
    vector<int> sum(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i - 1] + a[i - 1];
    }

    // DP数组，dp[i][j]表示合并第i到第j堆石子的最小代价
    vector<vector<int>> dp(n, vector<int>(n, INF));
    for (int i = 0; i < n; ++i) {
        dp[i][i] = 0;  // 单堆石子不需要合并
    }

    // 区间DP
    for (int l = 2; l <= n; ++l) {  // 枚举区间长度
        for (int i = 0; i + l - 1 < n; ++i) {  // 枚举区间起点
            int j = i + l - 1;  // 区间终点
            for (int k = i; k < j; ++k) {  // 枚举分割点
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + sum[j + 1] - sum[i]);
            }
        }
    }

    // 输出结果
    cout << dp[0][n - 1] << endl;

    return 0;
}