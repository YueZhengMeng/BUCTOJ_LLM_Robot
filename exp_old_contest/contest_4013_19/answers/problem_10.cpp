/* 
  Problem K: password
  2D DP (rolling) for selecting exactly s from a[] and t from b[] 
  with at most one pick per pair
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s, t;
    cin >> n >> s >> t;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];

    // dp[j][k] = max sum with j picks from a, k picks from b after processing items
    const int NEG_INF = -1000000000;
    vector<vector<int>> dp(s+1, vector<int>(t+1, NEG_INF));
    dp[0][0] = 0;

    for(int i = 0; i < n; i++) {
        // Traverse in descending order to roll in-place
        for(int j = s; j >= 0; j--) {
            for(int k = t; k >= 0; k--) {
                int cur = dp[j][k];
                if (cur < 0 && j != 0 || k != 0) {
                    // dp[j][k] might be NEG_INF, skip updates from it if invalid
                }
                // Option 1: pick a[i]
                if (j > 0 && dp[j-1][k] != NEG_INF) {
                    dp[j][k] = max(dp[j][k], dp[j-1][k] + a[i]);
                }
                // Option 2: pick b[i]
                if (k > 0 && dp[j][k-1] != NEG_INF) {
                    dp[j][k] = max(dp[j][k], dp[j][k-1] + b[i]);
                }
                // Option 0 (skip) is implicit: dp[j][k] remains
            }
        }
    }

    // The answer is the max sum taking exactly s from a and t from b
    cout << dp[s][t] << "\n";
    return 0;
}