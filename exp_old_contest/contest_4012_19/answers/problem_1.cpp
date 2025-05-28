/* 
  Problem: 姐就是女王 (Make your army size fall within [L, R] 
  by choosing one of two soldier additions per door.)
  Technique: Bitset DP with shifts
  Time: O(n * R/64), Space: O(R)
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, L, R;
    cin >> n >> L >> R;

    // dp[s] == 1 if we can reach army size s
    const int MAXR = 5000;
    bitset<MAXR+1> dp, next_dp;
    
    // initial army size = 1
    dp.reset();
    dp[1] = 1;

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        next_dp.reset();
        // shift left by x or y to simulate adding x or y soldiers
        if (x <= MAXR) next_dp |= (dp << x);
        if (y <= MAXR) next_dp |= (dp << y);
        dp = next_dp;
    }

    // Check if any reachable sum in [L, R]
    for (int s = L; s <= R; s++) {
        if (dp[s]) {
            cout << "Yes\n";
            return 0;
        }
    }
    cout << "No\n";
    return 0;
}