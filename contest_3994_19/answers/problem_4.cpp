/* 
  Problem: 天天苹果 (Minimize doctor visits)
  Algorithm: 3D DP (days × apples used × prev_zero flag)
  Key Tricks:
    1. State compress to prev day zero flag
    2. O(n·a) time, O(n·a) space
    3. 防御性编程处理 n=0 或 a=0 情况
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;

constexpr int MAXN = 1000 + 5;
constexpr int MAXA = 1000 + 5;

int dp[MAXN][MAXA][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a;
    cin >> n >> a;
    // 防御：确保 a 不超过 n
    if (a > n) a = n;

    // 初始化
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= a; j++) {
            dp[i][j][0] = dp[i][j][1] = INF;
        }
    }
    // 初始状态：0天、0个苹果、prev_zero=0
    dp[0][0][0] = 0;

    // DP 转移
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= a; j++) {
            for (int pz = 0; pz <= 1; pz++) {
                int cur = dp[i-1][j][pz];
                if (cur >= INF) continue;
                // 1) 第i天吃苹果
                if (j + 1 <= a) {
                    // DEBUG: 吃苹果后 prev_zero 清零，无新增访问
                    dp[i][j+1][0] = min(dp[i][j+1][0], cur);
                }
                // 2) 第i天不吃苹果
                {
                    // 如果前一天也未吃(pz==1)，则今天会被访问一次
                    int add = (pz == 1 ? 1 : 0);
                    // DEBUG: 不吃苹果后 prev_zero=1
                    dp[i][j][1] = min(dp[i][j][1], cur + add);
                }
            }
        }
    }

    // 从两种 prev_zero 状态中取最小
    int ans = min(dp[n][a][0], dp[n][a][1]);
    cout << ans << "\n";
    return 0;
}