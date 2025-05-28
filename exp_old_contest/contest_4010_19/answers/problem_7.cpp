/* 
  Problem H: Find the missing floor number x if sum of 1..n minus x equals S'.
  Key idea: Solve n(n+1)/2 ≥ S', then x = T_n - S'; if x==0, use next n.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        ll Sp;
        cin >> Sp;
        // Solve n(n+1)/2 >= Sp via quadratic formula
        // n ≈ (sqrt(8*Sp + 1) - 1) / 2, take ceiling
        double disc = sqrt(8.0 * Sp + 1.0);
        ll n = (ll)ceil((disc - 1.0) / 2.0);

        ll Tn = n * (n + 1) / 2;
        ll x = Tn - Sp;
        // If x == 0, Sp was exactly Tn; use next triangular
        if (x == 0) {
            n++;
            Tn = n * (n + 1) / 2;
            x = Tn - Sp;
        }
        cout << x << "\n";
    }
    return 0;
}