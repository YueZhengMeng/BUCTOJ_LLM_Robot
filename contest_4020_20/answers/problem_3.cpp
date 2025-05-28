#include <iostream>
#include <vector>
#include <queue>
#include <tuple> // Though a struct is used here
#include <algorithm> // For std::min
#include <limits>    // For std::numeric_limits

const int INF = std::numeric_limits<int>::max();

struct State {
    int r, c, steps;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> grid(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> grid[i][j];
        }
    }
    
    // dist[r][c][k] = min steps to reach (r,c) such that (total steps taken) % 3 == k
    std::vector<std::vector<std::vector<int>>> dist(n, std::vector<std::vector<int>>(n, std::vector<int>(3, INF)));
    std::queue<State> q;

    // Start at (0,0) with 0 steps. 0 % 3 = 0.
    dist[0][0][0] = 0;
    q.push({0, 0, 0});

    int dr[] = {-1, 1, 0, 0}; // Changes in row for up, down
    int dc[] = {0, 0, -1, 1}; // Changes in col for left, right

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        int r = current.r;
        int c = current.c;
        int s = current.steps;

        // If we later find a shorter path to this exact state (r, c, s%3)
        // and re-add it to queue, this check ensures we only process the shortest one.
        // Note: Standard BFS structure ensures this is implicitly handled if items are added
        // to queue only when a shorter path is found.
        // Here, if s > dist[r][c][s%3], it means a shorter path to this state was already processed.
        if (s > dist[r][c][s % 3]) {
            continue;
        }

        int current_val = grid[r][c];
        bool current_is_odd = (current_val % 2 != 0);

        // rule_type for the (s+1)-th step (the one we are about to take)
        int rule_type = s % 3; 

        for (int i = 0; i < 4; ++i) { // Iterate over 4 possible directions
            int nr = r + dr[i];
            int nc = c + dc[i];

            // Check bounds
            if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                int next_val = grid[nr][nc];
                bool next_is_odd = (next_val % 2 != 0);
                bool can_move = false;

                if (rule_type == 0) { // Rule for 1st, 4th, ... step type: Odd -> Even
                    if (current_is_odd && !next_is_odd) {
                        can_move = true;
                    }
                } else if (rule_type == 1) { // Rule for 2nd, 5th, ... step type: Even -> Odd
                    if (!current_is_odd && next_is_odd) {
                        can_move = true;
                    }
                } else { // rule_type == 2, Rule for 3rd, 6th, ... step type: Same parity
                    if (current_is_odd == next_is_odd) {
                        can_move = true;
                    }
                }

                if (can_move) {
                    int new_steps = s + 1;
                    int new_steps_mod_3 = new_steps % 3;
                    if (new_steps < dist[nr][nc][new_steps_mod_3]) {
                        dist[nr][nc][new_steps_mod_3] = new_steps;
                        q.push({nr, nc, new_steps});
                    }
                }
            }
        }
    }

    int min_steps_to_target = INF;
    for (int k = 0; k < 3; ++k) {
        min_steps_to_target = std::min(min_steps_to_target, dist[n - 1][n - 1][k]);
    }

    if (min_steps_to_target == INF) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << min_steps_to_target << std::endl;
    }

    return 0;
}