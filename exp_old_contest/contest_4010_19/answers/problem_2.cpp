/* 
   Problem: Split permutation-cycles so no cycle length > n using minimum swaps.
   Key Technique: Cycle decomposition + greedy splitting (each swap splits one cycle into two).
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int N = 2 * n;
    vector<int> P(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> P[i];
    }

    vector<bool> visited(N + 1, false);
    long long answer = 0;

    // Decompose permutation into cycles
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            int len = 0;
            int cur = i;
            // Traverse this cycle
            while (!visited[cur]) {
                visited[cur] = true;
                cur = P[cur];
                len++;
            }
            // If cycle length > n, we need splits
            if (len > n) {
                // Number of pieces = ceil(len / n), swaps = pieces - 1
                int pieces = (len + n - 1) / n;
                answer += (pieces - 1);
            }
        }
    }

    cout << answer << "\n";
    return 0;
}