/* 
   Author: Expert CP coder
   Algorithm: Two‐state Markov Chain closed‐form
   Key idea: f[n] = (1-p-q) * f[n-1] + q => solve linear recurrence
*/
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double p, q;
    int x;
    cin >> p >> q >> x;

    // Edge case: p = q = 0 => never switch, always G
    if (p == 0.0 && q == 0.0) {
        // for any x, probability of G is 1
        cout << fixed << setprecision(10) << 1.0 << "\n";
        return 0;
    }

    double a = 1.0 - p - q;     // recurrence multiplier
    // Compute a^(x-1)
    double a_pow = pow(a, x - 1);
    // Closed‐form: (q + p * a^(x-1)) / (p + q)
    double ans = (q + p * a_pow) / (p + q);

    cout << fixed << setprecision(10) << ans << "\n";
    return 0;
}