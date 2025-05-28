/* 文件头注释：最优二叉搜索树问题，使用动态规划求解 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<double> p(n), q(n + 1);
        for (int i = 0; i < n; ++i) cin >> p[i];
        for (int i = 0; i <= n; ++i) cin >> q[i];

        // dp[i][j] 表示区间 [i, j] 的最小搜索成本
        // sum[i][j] 表示区间 [i, j] 的概率和
        vector<vector<double>> dp(n + 2, vector<double>(n + 2, 0));
        vector<vector<double>> sum(n + 2, vector<double>(n + 2, 0));

        // 初始化 sum 数组
        for (int i = 1; i <= n; ++i) {
            sum[i][i] = p[i - 1] + q[i - 1] + q[i];
            dp[i][i] = sum[i][i];
        }

        // 动态规划求解
        for (int len = 2; len <= n; ++len) {
            for (int i = 1; i <= n - len + 1; ++i) {
                int j = i + len - 1;
                sum[i][j] = sum[i][j - 1] + p[j - 1] + q[j];
                dp[i][j] = numeric_limits<double>::max();
                for (int r = i; r <= j; ++r) {
                    double cost = dp[i][r - 1] + dp[r + 1][j] + sum[i][j];
                    if (cost < dp[i][j]) {
                        dp[i][j] = cost;
                    }
                }
            }
        }

        // 输出结果，保留两位小数
        cout << fixed << setprecision(2) << dp[1][n] << endl;
    }
    return 0;
}