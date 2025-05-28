#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // For memset or manual loop initialization

// A large enough value for infinity.
// Maximum possible path cost: (n-1) * max_edge_cost = 19 * 10^7 = 1.9 * 10^8.
// So 10^9 is a safe choice for INF.
const int INF = 1e9; 

int n;
// cost[i][j] stores the distance between node i and node j.
// n <= 20, so indices 0-19. Array size 20x20 is sufficient.
int cost[20][20]; 
// dp[mask][i] stores the shortest path visiting nodes in 'mask', starting at 0, and ending at node 'i'.
// Max mask is (1<<20)-1. Max i is 19.
int dp[1 << 20][20]; 

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> cost[i][j];
        }
    }

    // Initialize dp table with infinity
    for (int i = 0; i < (1 << n); ++i) {
        for (int j = 0; j < n; ++j) {
            dp[i][j] = INF;
        }
    }

    // Base case: The path starts at node 0, has only visited node 0, and ends at node 0.
    // The mask for "only node 0 visited" is (1 << 0).
    // This check handles n=0, though problem constraints usually imply n >= 1.
    if (n == 0) {
        std::cout << 0 << std::endl;
        return 0;
    }
    
    dp[1 << 0][0] = 0;

    // Iterate over all possible masks (subsets of visited nodes)
    for (int mask = 1; mask < (1 << n); ++mask) {
        // Iterate over all nodes 'j' which could be the last node in the path for 'mask'
        for (int j = 0; j < n; ++j) {
            // Check if node 'j' is actually part of the current 'mask'
            if (!((mask >> j) & 1)) {
                continue; // Node 'j' is not in mask, so dp[mask][j] is not relevant here.
            }

            // If dp[mask][j] is INF, it means this state (path to 'j' covering 'mask') is unreachable.
            if (dp[mask][j] == INF) {
                continue;
            }

            // Try to extend the path from node 'j' to a new node 'k'
            for (int k = 0; k < n; ++k) {
                // Check if node 'k' is NOT in the current 'mask' (i.e., not visited yet in this path)
                if (!((mask >> k) & 1)) {
                    int next_mask = mask | (1 << k); // Add node 'k' to the set of visited nodes
                    int new_cost = dp[mask][j] + cost[j][k];

                    // If this new path to 'k' (via 'j') is shorter, update dp[next_mask][k]
                    if (new_cost < dp[next_mask][k]) {
                        dp[next_mask][k] = new_cost;
                    }
                }
            }
        }
    }

    // The final answer is the shortest path that visits ALL nodes (mask (1 << n) - 1)
    // and ends at node n-1.
    int final_mask = (1 << n) - 1;
    
    // If n=1, final_mask is 1 (binary 0...01), n-1 is 0. dp[1][0] should be 0.
    // This will be dp[final_mask][n-1] if n-1 is a valid index.
    if (dp[final_mask][n - 1] == INF) {
        // This case should ideally not be reached if a Hamilton path always exists as per problem statement.
        // For robustness, one might print an error or a specific value.
        // However, typical contest problems asking for "the shortest" imply one exists.
        // Let's assume the problem guarantees a path exists.
         std::cout << -1 << std::endl; // Or some indicator of no path, if that's possible.
                                      // Given the problem implies existence, this should be the calculated value.
    } else {
        std::cout << dp[final_mask][n - 1] << std::endl;
    }

    return 0;
}