#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring> // For memset, though not strictly necessary for global static arrays

const int MAX_NODES = 100005; // N <= 100000. Nodes are 1-indexed.

std::vector<std::pair<int, int>> adj[MAX_NODES]; // adj[u] stores pairs {v, weight}
int out_degree[MAX_NODES];
double memo_dp[MAX_NODES];
bool calculated[MAX_NODES];
int N_actual_nodes; // Store the N from input

double calculate_expected_length(int u) {
    if (u == N_actual_nodes) {
        return 0.0;
    }
    if (calculated[u]) {
        return memo_dp[u];
    }

    double sum_of_weighted_expected_values = 0.0;
    
    for (const auto& edge : adj[u]) {
        int v = edge.first;
        int weight = edge.second;
        sum_of_weighted_expected_values += (double)weight + calculate_expected_length(v);
    }

    // It's implied by the problem expecting a finite answer that out_degree[u] > 0 
    // for any non-destination node u that is part of the recursive computation.
    // If out_degree[u] were 0 for u != N_actual_nodes, sum_of_weighted_expected_values would be 0,
    // and 0.0/0.0 would result in NaN, propagating upwards.
    if (out_degree[u] > 0) {
        memo_dp[u] = sum_of_weighted_expected_values / out_degree[u];
    } else {
        // This case (u != N_actual_nodes and out_degree[u] == 0) means the frog is stuck
        // and cannot reach N_actual_nodes. The expected length would be infinite.
        // For this problem, such a state being reachable and leading to a finite overall
        // expectation is unlikely. If it happened, memo_dp[u] would effectively be 0.0/0.0 (NaN).
        // We rely on the problem structure ensuring this isn't an issue for a valid finite answer.
        // If sum_of_weighted_expected_values is 0 (because adj[u] is empty) and out_degree[u] is 0, this leads to NaN.
        memo_dp[u] = sum_of_weighted_expected_values / out_degree[u]; // This will be NaN if out_degree[u] is 0.
    }
    

    calculated[u] = true;
    return memo_dp[u];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int M_edges;
    std::cin >> N_actual_nodes >> M_edges;

    // Global static arrays are zero-initialized by default.
    // `out_degree` elements will be 0, `calculated` elements will be false.
    // Explicit initialization for the relevant range can be done if preferred:
    /*
    for (int i = 1; i <= N_actual_nodes; ++i) {
        adj[i].clear(); 
        out_degree[i] = 0;
        calculated[i] = false;
    }
    */

    for (int i = 0; i < M_edges; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        adj[u].push_back({v, w});
        out_degree[u]++;
    }

    double result = calculate_expected_length(1);

    std::cout << std::fixed << std::setprecision(2) << result << std::endl;

    return 0;
}