/* 代码头注释：说明算法名称和关键技巧 */
// 算法名称：动态规划结合KMP算法
// 关键技巧：使用KMP算法预处理危险片段，动态规划计数不包含危险片段的DNA序列

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

void computeLPSArray(const string& pattern, vector<int>& lps) {
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < pattern.size()) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    string S;
    cin >> S;

    vector<int> lps(k);
    computeLPSArray(S, lps);

    vector<vector<ll>> dp(n + 1, vector<ll>(k + 1, 0));
    dp[0][0] = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            if (dp[i][j] == 0) continue;
            for (char c : {'A', 'T', 'C', 'G'}) {
                int nj = j;
                while (nj > 0 && S[nj] != c) {
                    nj = lps[nj - 1];
                }
                if (S[nj] == c) {
                    nj++;
                }
                if (nj < k) {
                    dp[i + 1][nj] = (dp[i + 1][nj] + dp[i][j]) % MOD;
                }
            }
        }
    }

    ll result = 0;
    for (int j = 0; j < k; ++j) {
        result = (result + dp[n][j]) % MOD;
    }

    cout << result << endl;

    return 0;
}