#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits> // Not strictly needed with current INF definition

using namespace std;

// A large negative number to represent unreachable states or uninitialized states
const long long INF = -1e18; 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long m_initial;
    cin >> n >> m_initial;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<long long> caps_val;
    if (m_initial > 0) { // m_initial >= 1 from constraints
        long long current_m_val = m_initial;
        while (current_m_val > 0) {
            caps_val.push_back(current_m_val);
            current_m_val = (current_m_val * 2) / 3;
        }
    }
    // If m_initial is 0 (not per constraints), caps_val would be empty.
    // Problem constraints 1 <= m <= 20000, so m_initial > 0 and caps_val will not be empty.
    int num_cap_levels = caps_val.size();


    // dp[i][j][k]
    // i: dishes processed + 1 (index from 0 to n)
    // j: skip_state at dish i-1 (0: ate, 1: skipped 1, 2: skipped >=2)
    // k: capacity_index relevant to state j
    //    size of k dimension is num_cap_levels (indices 0 to num_cap_levels-1)
    vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(3, vector<long long>(num_cap_levels, INF)));

    // Base case: before any dish (i=0), 0 calories, effectively >=2 skips.
    // k=0 is a placeholder for j=2 state.
    if (num_cap_levels > 0) { // This check is true due to m >= 1
      dp[0][2][0] = 0;
    } else { // This case should not be reached with m >= 1. If m=0, all calories are 0.
        cout << 0 << endl;
        return 0;
    }


    for (int i = 0; i < n; ++i) { // Current dish is a[i] (0-indexed for a, dp table uses i for previous dish)
        // Iterate over previous states (after dish i-1, stored in dp[i])
        
        // Case 1: prev_s = 0 (ate dish i-1, used capacity caps_val[prev_cap_idx])
        for (int prev_cap_idx = 0; prev_cap_idx < num_cap_levels; ++prev_cap_idx) {
            if (dp[i][0][prev_cap_idx] == INF) continue;

            // Option A: Eat dish a[i]
            int next_cap_idx_if_eat = prev_cap_idx + 1;
            if (next_cap_idx_if_eat < num_cap_levels) { 
                long long eaten_amount = min(a[i], caps_val[next_cap_idx_if_eat]);
                dp[i+1][0][next_cap_idx_if_eat] = max(dp[i+1][0][next_cap_idx_if_eat], dp[i][0][prev_cap_idx] + eaten_amount);
            }

            // Option B: Skip dish a[i]
            dp[i+1][1][prev_cap_idx] = max(dp[i+1][1][prev_cap_idx], dp[i][0][prev_cap_idx]);
        }

        // Case 2: prev_s = 1 (skipped dish i-1, ate dish i-2 with caps_val[cap_idx_before_skip])
        for (int cap_idx_before_skip = 0; cap_idx_before_skip < num_cap_levels; ++cap_idx_before_skip) {
            if (dp[i][1][cap_idx_before_skip] == INF) continue;

            // Option A: Eat dish a[i]
            // Capacity is caps_val[cap_idx_before_skip]
            long long eaten_amount = min(a[i], caps_val[cap_idx_before_skip]);
            dp[i+1][0][cap_idx_before_skip] = max(dp[i+1][0][cap_idx_before_skip], dp[i][1][cap_idx_before_skip] + eaten_amount);
            
            // Option B: Skip dish a[i] (now 2 consecutive skips)
            // k=0 is placeholder for skip_state = 2
            dp[i+1][2][0] = max(dp[i+1][2][0], dp[i][1][cap_idx_before_skip]);
        }

        // Case 3: prev_s = 2 (skipped dish i-1 and i-2 or more. prev_k is 0)
        if (dp[i][2][0] != INF) { 
            // Option A: Eat dish a[i]
            // Capacity is m = caps_val[0]
            long long eaten_amount = min(a[i], caps_val[0]); // caps_val[0] exists as num_cap_levels > 0
            dp[i+1][0][0] = max(dp[i+1][0][0], dp[i][2][0] + eaten_amount);

            // Option B: Skip dish a[i] (still >=2 skips)
            dp[i+1][2][0] = max(dp[i+1][2][0], dp[i][2][0]);
        }
    }

    long long max_calories = 0; // Minimum possible calories is 0
    for (int k_idx = 0; k_idx < num_cap_levels; ++k_idx) {
        if (dp[n][0][k_idx] != INF) max_calories = max(max_calories, dp[n][0][k_idx]);
        if (dp[n][1][k_idx] != INF) max_calories = max(max_calories, dp[n][1][k_idx]);
    }
    if (dp[n][2][0] != INF) max_calories = max(max_calories, dp[n][2][0]);
    
    cout << max_calories << endl;

    return 0;
}