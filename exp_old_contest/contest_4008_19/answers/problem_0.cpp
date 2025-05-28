/* 
   Problem A: Maximize LCM by choosing summands summing to N.
   Key idea: pick a subset of primes (0/1-knapsack on weight=prime, value=log(prime))
   to maximize sum of logs ⇒ maximize product ⇒ maximize LCM.
   Pad with 1s to reach sum N; tie-break by fewer total prime‐sum (more leading 1s).
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // 1. Sieve primes up to N
    vector<bool> is_composite(N+1, false);
    vector<int> primes;
    for (int i = 2; i <= N; i++) {
        if (!is_composite[i]) {
            primes.push_back(i);
            if ((long long)i * i <= N) {
                for (int j = i*i; j <= N; j += i)
                    is_composite[j] = true;
            }
        }
    }

    // 2. Knapsack DP: dp[j] = max sum of logs for total weight j
    const double NEG_INF = -1e100;
    vector<double> dp(N+1, NEG_INF);
    vector<int> prev_idx(N+1, -1), choice(N+1, -1);
    dp[0] = 0.0;

    for (int i = 0; i < (int)primes.size(); i++) {
        int p = primes[i];
        double lp = log((double)p);
        // 0/1 knapsack: iterate backwards on weight
        for (int w = N; w >= p; w--) {
            double cand = dp[w-p] + lp;
            if (cand > dp[w] + 1e-12) {
                dp[w] = cand;
                prev_idx[w] = w - p;
                choice[w] = i;
            }
        }
    }

    // 3. Find best total prime-sum w ≤ N that maximizes dp[w], tie-breaking on smaller w
    double best_val = 0.0;
    int best_w = 0;
    for (int w = 1; w <= N; w++) {
        if (dp[w] > best_val + 1e-12 ||
           (fabs(dp[w] - best_val) < 1e-12 && w < best_w)) {
            best_val = dp[w];
            best_w = w;
        }
    }

    // 4. Reconstruct chosen primes
    vector<int> chosen;
    int cur = best_w;
    while (cur > 0 && choice[cur] != -1) {
        int idx = choice[cur];
        chosen.push_back(primes[idx]);
        cur = prev_idx[cur];
    }
    sort(chosen.begin(), chosen.end());

    // 5. Output: (N - best_w) ones, then the chosen primes
    int ones = N - best_w;
    bool first = true;
    for (int i = 0; i < ones; i++) {
        if (!first) cout << ' ';
        cout << 1;
        first = false;
    }
    for (int p: chosen) {
        if (!first) cout << ' ';
        cout << p;
        first = false;
    }
    // Special case: if N == 0 or N == 1, we should at least print one '1'
    if (N == 1) {
        if (!first) cout << ' ';
        cout << 1;
    }
    cout << "\n";
    return 0;
}