#include <iostream>
#include <vector>
#include <algorithm> // For std::max

// Global variables for convenience
int N_nodes; // Number of employees
std::vector<int> happiness; // Stores happiness H_i for employee i
std::vector<std::vector<int>> adj_list; // Adjacency list for the tree (parent -> children)
std::vector<std::vector<int>> memo_dp; // DP table: memo_dp[i][0] -> i not attending, memo_dp[i][1] -> i attending

// DFS function to compute DP states
void solve_dfs(int u) {
    // Initialize DP states for the current node u
    // If u does not attend, initial happiness sum from this branch is 0.
    memo_dp[u][0] = 0;
    // If u attends, initial happiness sum is H[u].
    memo_dp[u][1] = happiness[u];

    // Iterate over all direct children (subordinates) v of u
    for (int v : adj_list[u]) {
        solve_dfs(v); // Recursively solve for child v first

        // If u does not attend (memo_dp[u][0]):
        // Child v can either attend (memo_dp[v][1]) or not attend (memo_dp[v][0]).
        // We add the maximum possible happiness from v's subtree to u's total.
        memo_dp[u][0] += std::max(memo_dp[v][0], memo_dp[v][1]);

        // If u attends (memo_dp[u][1]):
        // Child v cannot attend (because u is v's direct supervisor).
        // So we add happiness from v's subtree assuming v does not attend (memo_dp[v][0]).
        memo_dp[u][1] += memo_dp[v][0];
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cin >> N_nodes;

    happiness.resize(N_nodes + 1);
    adj_list.resize(N_nodes + 1);
    // Happiness values are between -128 and 127. Max N is 6000.
    // Max sum: 6000 * 127 = 762,000. Min sum: 6000 * -128 = -768,000.
    // These values fit within a standard 32-bit integer.
    memo_dp.resize(N_nodes + 1, std::vector<int>(2));
    
    std::vector<bool> has_direct_supervisor(N_nodes + 1, false);

    for (int i = 1; i <= N_nodes; ++i) {
        std::cin >> happiness[i];
    }

    int subordinate, supervisor;
    // Read supervisor-subordinate pairs until 0 0
    while (std::cin >> subordinate >> supervisor && (subordinate != 0 || supervisor != 0)) {
        adj_list[supervisor].push_back(subordinate); // K (supervisor) is parent of L (subordinate)
        has_direct_supervisor[subordinate] = true;
    }

    int root_employee = -1;
    // Find the root (employee with no supervisor)
    // This loop will find the root correctly even if N_nodes = 1.
    for (int i = 1; i <= N_nodes; ++i) {
        if (!has_direct_supervisor[i]) {
            root_employee = i;
            break; 
        }
    }
    
    // Constraints: 1 <= N <= 6000. So N_nodes is at least 1.
    // A root must exist as per problem description "tree with the president as the root".
    if (N_nodes > 0) { // Defensive check, N_nodes always > 0 by constraints
        if (root_employee != -1) { // Root found
            solve_dfs(root_employee);
            std::cout << std::max(memo_dp[root_employee][0], memo_dp[root_employee][1]) << std::endl;
        } else {
            // This case implies no root was found, which contradicts problem statement for N > 0.
            // For N=1, the loop correctly finds employee 1 as root.
            // If N_nodes > 0 and root is -1, it suggests an issue not covered by typical problem scenarios.
            // However, given the problem guarantees, a root will be found.
        }
    } else { // N_nodes = 0 (not possible by constraints 1 <= N <= 6000)
        std::cout << 0 << std::endl; 
    }

    return 0;
}