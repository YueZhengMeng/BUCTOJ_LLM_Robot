/* 文件头注释：动态规划解决组合优化问题，使用优化后的状态转移方程降低时间复杂度 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, s, t;
    cin >> n >> s >> t;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    // 初始化 DP 数组
    // dp[i][j] 表示处理到第 i 个元素，从 a 中选择了 j 个元素的最大得分
    vector<vector<int>> dp(n + 1, vector<int>(s + 1, -1));
    dp[0][0] = 0;

    // 动态规划转移
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= s; ++j) {
            if (dp[i - 1][j] == -1) continue;
            // 不选 a[i-1] 也不选 b[i-1]
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
            // 选 a[i-1]
            if (j < s && (i - 1 - j) <= t) {
                dp[i][j + 1] = max(dp[i][j + 1], dp[i - 1][j] + a[i - 1]);
            }
            // 选 b[i-1]
            if (j <= s && (i - j) <= t) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j] + b[i - 1]);
            }
        }
    }

    // 输出最大得分
    cout << dp[n][s] << endl;
    return 0;
}