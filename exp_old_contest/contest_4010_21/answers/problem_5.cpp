/* 文件头注释：动态规划与排序结合，计算严格递增序列的方案数 */
/* 主要修改标记：[FIX] 使用前缀和优化和二分查找降低时间复杂度 */
#include <bits/stdc++.h>
using namespace std;

const int MOD = 19260817;

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<vector<int>> matrix(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> matrix[i][j];
        }
        sort(matrix[i].begin(), matrix[i].end()); // 对每一行进行排序
    }
    
    vector<vector<int>> dp(N, vector<int>(M, 0));
    for (int j = 0; j < M; ++j) {
        dp[0][j] = 1; // 第一行的每个元素都是一种方案
    }
    
    for (int i = 1; i < N; ++i) {
        // 计算前一行的前缀和
        vector<int> prefixSum(M);
        prefixSum[0] = dp[i-1][0];
        for (int j = 1; j < M; ++j) {
            prefixSum[j] = (prefixSum[j-1] + dp[i-1][j]) % MOD;
        }
        
        for (int j = 0; j < M; ++j) {
            // 使用二分查找找到前一行的最后一个小于 matrix[i][j] 的元素位置
            auto it = lower_bound(matrix[i-1].begin(), matrix[i-1].end(), matrix[i][j]);
            int pos = it - matrix[i-1].begin();
            if (pos > 0) {
                dp[i][j] = prefixSum[pos-1];
            } else {
                dp[i][j] = 0;
            }
        }
    }
    
    int result = 0;
    for (int j = 0; j < M; ++j) {
        result = (result + dp[N-1][j]) % MOD;
    }
    
    cout << result << endl;
    return 0;
}