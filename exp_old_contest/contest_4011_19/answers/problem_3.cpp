/* 
  Algorithm: Pair stones from different piles.
  Key trick: answer = min(totalStones/2, totalStones - maxPile)
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    long long total = 0;
    long long mx = 0;
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        total += x;
        mx = max(mx, x);
    }

    // Maximum moves bounded by total/2 and (total - largest pile)
    long long ans = min(total / 2, total - mx);
    cout << ans << "\n";
    return 0;
}