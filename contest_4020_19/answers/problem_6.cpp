/* 
  Algorithm: DP over candidate set S of "boundary" numbers
  Key Techniques: 
    1) Generate S = {0, powers of two, m, m with one 1-bit turned off + lows set}
    2) Also generate m with low bits zeroed (“prefix-zero”) to cover negative weights
    3) Ensure at least n candidates by adding [0..n-1]
    4) Compute popcounts
    5) DP[i][j] = best for first i picks ending at S[j], use prefix‐max for O(1) transitions
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (ll)4e18;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll m;
    cin >> n >> m;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    // 1) Build heuristic candidate set S
    vector<ll> S;
    S.push_back(0);
    // powers of two
    for(int b = 0; b < 63; b++){
        ll x = (1ULL << b);
        if(x <= m) S.push_back(x);
        else break;
    }
    // m itself
    S.push_back(m);
    // For each 1-bit in m, clear it and set all lower bits to 1
    for(int b = 0; b < 63; b++){
        if((m >> b) & 1){
            ll x = m;
            x &= ~(1ULL << b);           // clear bit b
            ll lowerMask = (1ULL << b) - 1;
            x |= lowerMask;              // set all bits < b
            S.push_back(x);
        }
    }
    // NEW: Also generate “prefix-zero” variants (clear lowest b bits) for all b
    for(int b = 0; b < 63; b++){
        ll x = (m >> b) << b;  // clear bits [0..b-1]
        S.push_back(x);
    }
    // 1a) Ensure we have at least n distinct candidates by adding [0..n-1] (clamped by m)
    for(ll x = 0; x < (ll)n && x <= m; x++){
        S.push_back(x);
    }

    // sort & unique
    sort(S.begin(), S.end());
    S.erase(unique(S.begin(), S.end()), S.end());
    int M = S.size();

    // 2) Precompute popcounts
    vector<int> pc(M);
    for(int i = 0; i < M; i++){
        pc[i] = __builtin_popcountll(S[i]);
    }

    // 3) DP arrays: dp_prev = dp for i-1, dp_cur for i
    vector<ll> dp_prev(M, -INF), dp_cur(M, -INF);

    // Build DP layer by layer
    for(int i = 0; i < n; i++){
        // Compute prefix maxima of dp_prev
        vector<ll> prefMax(M, -INF);
        prefMax[0] = dp_prev[0];
        for(int j = 1; j < M; j++){
            prefMax[j] = max(prefMax[j-1], dp_prev[j]);
        }
        // Fill dp_cur
        for(int j = 0; j < M; j++){
            if(i == 0){
                // first pick: no prior constraint
                dp_cur[j] = (ll)pc[j] * a[i];
            } else {
                // need k < j
                if(j > 0 && prefMax[j-1] > -INF/2){
                    dp_cur[j] = prefMax[j-1] + (ll)pc[j] * a[i];
                } else {
                    dp_cur[j] = -INF;
                }
            }
        }
        dp_prev.swap(dp_cur);
    }

    // 4) Answer is max over dp_prev[j]
    ll ans = *max_element(dp_prev.begin(), dp_prev.end());
    cout << ans << "\n";
    return 0;
}