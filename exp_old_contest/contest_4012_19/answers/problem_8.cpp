/* 
  Algorithm: Inverse moves via Euclidean steps
  Key idea: Reverse from (p,q) to (1,1), recording L/R in batches 
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long p, q;
    cin >> p >> q;

    string ans;
    ans.reserve(p + q);  // max possible length

    // Apply Euclidean-like steps while both >1
    while (p > 1 && q > 1) {
        if (p > q) {
            long long times = p / q;
            ans.append(times, 'L');
            p %= q;
        } else {
            long long times = q / p;
            ans.append(times, 'R');
            q %= p;
        }
    }

    // One of them is 1, append the remaining moves in one batch
    if (p == 1) {
        // We have 1/q, need (q-1) R-steps backward
        ans.append(q - 1, 'R');
    } else {
        // We have p/1, need (p-1) L-steps backward
        ans.append(p - 1, 'L');
    }

    // We built the path backward; reverse it
    reverse(ans.begin(), ans.end());

    cout << ans << "\n";
    return 0;
}