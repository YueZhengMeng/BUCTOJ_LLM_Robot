/* 代码头注释：说明算法名称和关键技巧 */
// 算法名称：0-1 背包问题
// 关键技巧：动态规划 + 滚动数组优化
// 时间复杂度：O(N*V)
// 空间复杂度：O(V)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, V;
        cin >> N >> V;
        vector<int> value(N), volume(N);
        for (int i = 0; i < N; ++i) cin >> value[i];
        for (int i = 0; i < N; ++i) cin >> volume[i];

        // 初始化 dp 数组
        vector<int> dp(V + 1, 0);

        // 动态规划过程
        for (int i = 0; i < N; ++i) {
            for (int j = V; j >= volume[i]; --j) {
                dp[j] = max(dp[j], dp[j - volume[i]] + value[i]);
            }
        }

        // 输出结果
        cout << dp[V] << "\n";
    }

    return 0;
}