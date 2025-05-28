/* 
  Problem C: PolarBear's Path Sum
  Key technique: 
    - Compute min sum (all Ups then all Rights),
    - each UR→RU swap raises sum by (n-1),
    - max swaps = (n-1)^2 ⇒ max_sum = min_sum + (n-1)^3.
    - Check k in [min_sum, max_sum] and congruent mod (n-1).
*/
#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int64 n, k;
        cin >> n >> k;
        // Compute min_sum = n*(n^2 + 2n - 1)/2
        // Compute max_sum = min_sum + (n-1)^3
        __int128 N = n;
        __int128 min_sum = N*(N*N + 2*N - 1) / 2;
        __int128 delta = (N-1)*(N-1)*(N-1);
        __int128 max_sum = min_sum + delta;
        __int128 K = k;

        bool ok = false;
        if (K >= min_sum && K <= max_sum) {
            // Check (K - min_sum) % (n-1) == 0
            int64 mod = n - 1;
            // We can reduce (K - min_sum) mod mod safely in 128-bit:
            __int128 diff = K - min_sum;
            if ((diff % mod) == 0) ok = true;
        }
        cout << (ok ? "YES\n" : "NO\n");
    }
    return 0;
}