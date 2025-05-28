/* 代码头注释：说明算法名称和关键技巧 */
// 算法名称：动态规划 + KMP 算法
// 关键技巧：使用 KMP 算法预处理危险片段 S，快速计算匹配状态，使用动态规划记录不包含 S 的序列数量。

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    string S;
    cin >> n >> k >> S;

    // KMP 预处理
    vector<int> lps(k, 0);
    for (int i = 1, len = 0; i < k;) {
        if (S[i] == S[len]) {
            lps[i++] = ++len;
        } else if (len != 0) {
            len = lps[len - 1];
        } else {
            lps[i++] = 0;
        }
    }

    // DP 状态转移
    vector<vector<ll>> dp(n + 1, vector<ll>(k + 1, 0));
    dp[0][0] = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            if (dp[i][j] == 0) continue;
            for (char c : {'A', 'T', 'C', 'G'}) {
                int nj = j;
                while (nj > 0 && c != S[nj]) {
                    nj = lps[nj - 1];
                }
                if (c == S[nj]) {
                    ++nj;
                }
                if (nj < k) {
                    dp[i + 1][nj] = (dp[i + 1][nj] + dp[i][j]) % MOD;
                }
            }
        }
    }

    // 计算结果
    ll result = 0;
    for (int j = 0; j < k; ++j) {
        result = (result + dp[n][j]) % MOD;
    }

    cout << result << endl;

    return 0;
}