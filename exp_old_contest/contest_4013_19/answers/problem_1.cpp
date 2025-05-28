/* 
  Algorithm: Greedy Simulation of Sequential Mergers
  Key Technique: Maintain running charm T; for each opponent M[i], check T > M[i].
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, n;
    cin >> T >> n;
    vector<int> M(n);
    for (int i = 0; i < n; i++) {
        cin >> M[i];
    }

    for (int mi : M) {
        // If T is not strictly greater, T cannot become queen
        if (T <= mi) {
            cout << "Oh no, so charming she is." << "\n";
            return 0;
        }
        T += mi;  // conquer and merge charms
    }

    // If all conquered successfully
    cout << "I'm the queen today!" << "\n";
    return 0;
}