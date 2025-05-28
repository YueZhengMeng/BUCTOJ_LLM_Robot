/* 文件头注释：动态规划解决小Z的烧烤规划问题 */
/* 主要修改标记：[FIX] 修正卡路里限制更新方式，优化状态转移方程 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // dp[i][j]表示在第i道菜时，当前卡路里限制为j时的最大总卡路里
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    // skip_count[i]表示在第i道菜时连续不吃的小时数
    vector<int> skip_count(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            // 不吃当前菜
            int new_skip = skip_count[i - 1] + 1;
            if (new_skip >= 2) {
                dp[i][m] = max(dp[i][m], dp[i - 1][j]);
                skip_count[i] = 0;  // 重置连续不吃小时数
            } else {
                dp[i][j] = max(dp[i][j], dp[i - 1][j]);
                skip_count[i] = new_skip;
            }

            // 吃当前菜
            if (j >= a[i - 1]) {
                int new_limit = j * 2 / 3;  // 整数除法自动截断
                dp[i][new_limit] = max(dp[i][new_limit], dp[i - 1][j] + a[i - 1]);
                skip_count[i] = 0;  // 重置连续不吃小时数
            }
        }
    }

    // 找出最大总卡路里
    int max_calories = 0;
    for (int j = 0; j <= m; ++j) {
        max_calories = max(max_calories, dp[n][j]);
    }

    cout << max_calories << endl;
    return 0;
}