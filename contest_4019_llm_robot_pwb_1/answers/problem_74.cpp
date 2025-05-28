/* 文件头注释：0-1背包问题，动态规划解法 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; // 样例组数
    cin >> t;
    while (t--) {
        int n, W; // 物品个数和购物车容量
        cin >> n >> W;
        vector<int> w(n), v(n); // 物品的重量和价值
        for (int i = 0; i < n; ++i) {
            cin >> w[i] >> v[i];
        }
        
        // 初始化DP数组，dp[i][j]表示前i个物品在容量j下的最大价值
        vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
        
        // 动态规划填表
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= W; ++j) {
                if (j >= w[i - 1]) {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i - 1]] + v[i - 1]);
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        
        // 输出最大价值
        cout << dp[n][W] << endl;
    }
    return 0;
}