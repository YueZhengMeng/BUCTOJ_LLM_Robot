/* 
   Algorithm: Precompute per-row shooter positions and torch counts, with prefix sums.
   Query in O(log M + log K) using binary searches.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXR = 5;
const ll MOD = 998244353;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, q;
    cin >> n >> m >> k >> q;
    // For rows 1..5, store shooter columns and torch columns
    vector<ll> shooters[MAXR+1], torches[MAXR+1];
    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        shooters[x].push_back(y);
    }
    for(int i = 0; i < k; i++){
        int x, y;
        cin >> x >> y;
        torches[x].push_back(y);
    }
    // Precompute per-row sorted lists and prefix sums
    // prefS[r][i] = sum of the first i shooter columns in row r (1-based)
    // prefP[r][i] = sum of (#torches ≤ shooterCol) over the first i shooters
    vector<ll> prefS[MAXR+1], prefP[MAXR+1];
    for(int r = 1; r <= MAXR; r++){
        auto &S = shooters[r];
        auto &T = torches[r];
        sort(S.begin(), S.end());
        sort(T.begin(), T.end());
        int sz = (int)S.size();
        prefS[r].assign(sz+1, 0);
        prefP[r].assign(sz+1, 0);
        // Build prefix sum of shooter positions
        for(int i = 1; i <= sz; i++){
            prefS[r][i] = (prefS[r][i-1] + S[i-1]) % MOD;
        }
        // Build prefix sum of #torches ≤ S[i-1]
        ll accP = 0;
        for(int i = 1; i <= sz; i++){
            // count torches ≤ S[i-1]
            int cntT = int(upper_bound(T.begin(), T.end(), S[i-1]) - T.begin());
            accP = (accP + cntT) % MOD;
            prefP[r][i] = accP;
        }
    }

    // Answer queries
    while(q--){
        int x, y;
        cin >> x >> y;
        auto &S = shooters[x];
        auto &T = torches[x];
        auto &PS = prefS[x];
        auto &PP = prefP[x];
        // p = # shooters with col < y
        int p = int(lower_bound(S.begin(), S.end(), y) - S.begin());
        if(p == 0){
            cout << 0 << "\n";
            continue;
        }
        // Part1 = p*y - sum_{i=1..p} S[i-1]
        ll sumS = PS[p];  // modded
        ll part1 = ((ll)p * y % MOD - sumS + MOD) % MOD;
        // tc = # torches with col ≤ y
        ll tc = upper_bound(T.begin(), T.end(), y) - T.begin();
        // Part2 = 2 * (p*tc - sum_{i=1..p} P_i)
        ll sumP = PP[p];  // modded
        ll part2 = (( (ll)p * tc % MOD - sumP + MOD ) % MOD) * 2 % MOD;
        ll ans = (part1 + part2) % MOD;
        cout << ans << "\n";
    }
    return 0;
}