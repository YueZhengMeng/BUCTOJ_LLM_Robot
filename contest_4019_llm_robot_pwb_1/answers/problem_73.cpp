/* 文件头注释：矩阵链乘法问题，使用动态规划求解 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> dims(n + 1);
        for (int i = 0; i <= n; ++i) {
            cin >> dims[i];
        }
        
        // DP表，dp[i][j]表示从第i个矩阵到第j个矩阵的最小计算量
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // 填充DP表
        for (int len = 2; len <= n; ++len) { // len是矩阵链的长度
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;
                for (int k = i; k < j; ++k) {
                    // 计算当前分割点的计算量，并更新最小值
                    int cost = dp[i][k] + dp[k+1][j] + dims[i] * dims[k+1] * dims[j+1];
                    if (cost < dp[i][j]) {
                        dp[i][j] = cost;
                    }
                }
            }
        }
        
        // 输出从第1个矩阵到第n个矩阵的最小计算量
        cout << dp[0][n-1] << endl;
    }
    return 0;
}