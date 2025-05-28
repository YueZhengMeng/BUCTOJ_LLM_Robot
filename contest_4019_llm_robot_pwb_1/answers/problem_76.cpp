/* 文件头注释：0-1背包问题，动态规划解法 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, W;
        cin >> n >> W;
        vector<int> w(n), v(n);
        for (int i = 0; i < n; ++i) {
            cin >> w[i] >> v[i];
        }
        
        // dp[j]表示容量为j的购物车能装的最大价值
        vector<int> dp(W + 1, 0);
        
        // 动态规划填表
        for (int i = 0; i < n; ++i) {
            for (int j = W; j >= w[i]; --j) {
                dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
            }
        }
        
        // 输出最大价值
        cout << dp[W] << endl;
    }
    return 0;
}