/* 
  Problem: Count non-decreasing sequences of length N, max value M,
           given a[x] = y, modulo 1e9+7.
  Technique: Split at x into left DP (length x, end y) and right DP 
             (length N-x+1, start y), both using prefix-sum DP.
*/
#include <bits/stdc++.h>
using namespace std;
static const int MOD = 1000000007;

int add(int a, int b) {
    int s = a + b;
    if (s >= MOD) s -= MOD;
    return s;
}

int mul(long long a, long long b) {
    return int((a * b) % MOD);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;
    int x, y;
    cin >> x >> y;

    // DP for left part: length = x, values in [1..M]
    vector<int> dp_prev(M+1, 1), dp_curr(M+1), pref(M+1);
    // Base: length=1 => dp_prev[k] = 1 for all k

    for (int len = 2; len <= x; ++len) {
        // build prefix sums of dp_prev
        pref[0] = 0;
        for (int v = 1; v <= M; ++v) {
            pref[v] = add(pref[v-1], dp_prev[v]);
        }
        // dp_curr[v] = sum_{k<=v} dp_prev[k]
        for (int v = 1; v <= M; ++v) {
            dp_curr[v] = pref[v];
        }
        // swap for next iteration
        dp_prev.swap(dp_curr);
    }
    // ways for left part to end exactly at y
    int waysLeft = dp_prev[y];

    // DP for right part: length = L = N-x+1, values in [1..M], start at y
    int L = N - x + 1;
    // initialize dp_prev so that dp_prev[k] = 1 if k==y else 0
    fill(dp_prev.begin(), dp_prev.end(), 0);
    dp_prev[y] = 1;

    for (int len = 2; len <= L; ++len) {
        pref[0] = 0;
        for (int v = 1; v <= M; ++v) {
            pref[v] = add(pref[v-1], dp_prev[v]);
        }
        for (int v = 1; v <= M; ++v) {
            dp_curr[v] = pref[v];
        }
        dp_prev.swap(dp_curr);
    }
    // total ways for right part: any ending value >= y
    int waysRight = 0;
    for (int v = y; v <= M; ++v) {
        waysRight = add(waysRight, dp_prev[v]);
    }

    // final answer
    cout << mul(waysLeft, waysRight) << "\n";
    return 0;
}