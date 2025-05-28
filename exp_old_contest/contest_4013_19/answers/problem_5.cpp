/* 
  Algorithm: Simulate the two‐operation “arc+tan” step 
  which corresponds to one subtraction step in the Euclidean algorithm.
  We succeed iff gcd(a,b)==1 and the final 'y' when 'x' becomes 1 equals c. 
*/
#include <bits/stdc++.h>
using namespace std;

// Portable gcd implementation
long long gcd(long long u, long long v) {
    while (v) {
        long long t = u % v;
        u = v;
        v = t;
    }
    return u;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        long long a, b, c;
        cin >> a >> b >> c;

        // If gcd != 1, we can never get numerator = 1 exactly.
        if (gcd(a, b) != 1) {
            cout << "NO\n";
            continue;
        }

        // Run a Euclidean‐mod loop until the smaller becomes 1.
        long long x = a, y = b;
        while (x > 1) {
            long long r = y % x;
            y = x;
            x = r;
        }
        // Now x == 1, and y is the final denominator such that
        // we have transformed to sqrt(1/y).
        cout << (y == c ? "YES\n" : "NO\n");
    }
    return 0;
}