/* 
  Problem D: Overlapping Breaks
  Compute total overlap length of two periodic "break" schedules on [0, K).
  Technique: generate break intervals for each schedule, then two-pointer interval intersection.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll K, x, y, p, q;
    cin >> K >> x >> y >> p >> q;

    // Generate break intervals for schedule A: cycles of length (x+y)
    vector<pair<ll,ll>> A, B;
    ll cycleA = x + y;
    for (ll i = 0; ; i++) {
        ll start = i * cycleA + x;
        if (start >= K) break;
        ll end = start + y;
        if (end > K) end = K;
        A.emplace_back(start, end);
    }

    // Generate break intervals for schedule B: cycles of length (p+q)
    ll cycleB = p + q;
    for (ll j = 0; ; j++) {
        ll start = j * cycleB + p;
        if (start >= K) break;
        ll end = start + q;
        if (end > K) end = K;
        B.emplace_back(start, end);
    }

    // Two-pointer sweep to sum up intersections
    ll ans = 0;
    int i = 0, j = 0;
    while (i < (int)A.size() && j < (int)B.size()) {
        ll lA = A[i].first, rA = A[i].second;
        ll lB = B[j].first, rB = B[j].second;
        // Compute intersection
        ll L = max(lA, lB);
        ll R = min(rA, rB);
        if (L < R) {
            ans += (R - L);
        }
        // Advance the interval that ends first
        if (rA < rB) {
            i++;
        } else {
            j++;
        }
    }

    cout << ans << "\n";
    return 0;
}