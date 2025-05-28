#include <iostream>
#include <vector>
#include <algorithm> // For std::min
#include <limits>    // For std::numeric_limits

// Using long long for dp values and sums for safety, though int might suffice.
const long long INF = std::numeric_limits<long long>::max();

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<long long> a(n + 1);
    std::vector<long long> s(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        s[i] = s[i-1] + a[i];
    }

    if (n <= 1) {
        std::cout << 0 << std::endl;
        return 0;
    }

    std::vector<std::vector<long long>> dp(n + 1, std::vector<long long>(n + 1, 0));
    std::vector<std::vector<int>> K(n + 1, std::vector<int>(n + 1, 0));

    // Base cases: dp[i][i] = 0 (already initialized by 0 for dp table)
    // K[i][i] = i is a convention for the bounds of k search.
    for (int i = 1; i <= n; ++i) {
        K[i][i] = i;
    }

    // len is the length of the segment being merged
    for (int len = 2; len <= n; ++len) {
        // i is the starting pile index
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1; // ending pile index
            dp[i][j] = INF;
            long long current_pile_sum = s[j] - s[i-1];

            int k_lower_bound = K[i][j-1];
            int k_upper_bound_candidate = K[i+1][j];
            
            // The optimal split k for dp[i][j] must be i <= k < j.
            // The search range for k is [K[i][j-1], K[i+1][j]].
            // We must ensure k < j. K[i+1][j] might be j if len=2 and K[j][j]=j.
            // So, the actual upper limit for k in the loop should be min(j-1, K[i+1][j]).
            int actual_k_upper_bound = std::min(j - 1, k_upper_bound_candidate);
            
            int best_k_for_ij = k_lower_bound; // Default best_k initialization

            for (int k = k_lower_bound; k <= actual_k_upper_bound; ++k) {
                // k is the split point: merge piles (i..k) and (k+1..j)
                // By construction: i <= K[i][j-1] <= k
                // and k <= min(j-1, K[i+1][j]) implies k <= j-1 (so k < j).
                // Thus, k is a valid split index.
                long long temp_cost = dp[i][k] + dp[k+1][j] + current_pile_sum;
                if (temp_cost < dp[i][j]) {
                    dp[i][j] = temp_cost;
                    best_k_for_ij = k;
                }
            }
            K[i][j] = best_k_for_ij;
        }
    }

    std::cout << dp[1][n] << std::endl;

    return 0;
}