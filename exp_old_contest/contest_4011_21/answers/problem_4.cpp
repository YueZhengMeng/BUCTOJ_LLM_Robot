/* 文件头注释：动态规划 + 前缀和优化 */
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int N, M, x, y;
    cin >> N >> M >> x >> y;

    // 使用滚动数组优化空间复杂度
    vector<int> dp_prev(M + 1, 0);
    vector<int> dp_curr(M + 1, 0);
    vector<int> prefix_prev(M + 1, 0);
    vector<int> prefix_curr(M + 1, 0);

    // 初始化第 1 天
    for (int j = 1; j <= M; ++j) {
        dp_prev[j] = 1;
        prefix_prev[j] = (prefix_prev[j - 1] + dp_prev[j]) % MOD;
    }

    // 填充 DP 表
    for (int i = 2; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            if (i == x) {
                if (j == y) {
                    dp_curr[j] = prefix_prev[j];
                } else {
                    dp_curr[j] = 0;
                }
            } else {
                dp_curr[j] = prefix_prev[j];
            }
            prefix_curr[j] = (prefix_curr[j - 1] + dp_curr[j]) % MOD;
        }
        // 滚动数组更新
        swap(dp_prev, dp_curr);
        swap(prefix_prev, prefix_curr);
    }

    // 输出结果
    cout << prefix_prev[M] << endl;

    return 0;
}