/* 文件头注释：动态规划解决带约束的组合优化问题 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, s, t;
    cin >> n >> s >> t;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    // dp[i][j][k] 表示前 i 个元素中，从 a 数组中选择 j 个，从 b 数组中选择 k 个的最大得分
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(s + 1, vector<int>(t + 1, -1)));
    dp[0][0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= s; ++j) {
            for (int k = 0; k <= t; ++k) {
                if (dp[i - 1][j][k] == -1) continue; // 无效状态
                // 不选 a[i-1] 和 b[i-1]
                dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][k]);
                // 选 a[i-1]
                if (j < s) {
                    dp[i][j + 1][k] = max(dp[i][j + 1][k], dp[i - 1][j][k] + a[i - 1]);
                }
                // 选 b[i-1]
                if (k < t) {
                    dp[i][j][k + 1] = max(dp[i][j][k + 1], dp[i - 1][j][k] + b[i - 1]);
                }
            }
        }
    }

    cout << dp[n][s][t] << endl;
    return 0;
}