/* 代码头注释：动态规划解决超级楼梯问题，使用滚动数组优化空间复杂度 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    while (N--) {
        int M;
        cin >> M;

        // 边界条件处理
        if (M == 1) {
            cout << "1\n";
            continue;
        }
        if (M == 2) {
            cout << "1\n";
            continue;
        }

        // 动态规划，使用滚动数组
        int dp_prev_prev = 1; // dp[1]
        int dp_prev = 1;      // dp[2]
        int dp_curr = 0;

        for (int i = 3; i <= M; ++i) {
            dp_curr = dp_prev + dp_prev_prev;
            dp_prev_prev = dp_prev;
            dp_prev = dp_curr;
        }

        cout << dp_curr << "\n";
    }

    return 0;
}