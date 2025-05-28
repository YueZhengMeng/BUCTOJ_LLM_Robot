/* 
   Algorithm: Check if 1/x is a terminating decimal in base-10.
   Key idea: 1/x is finite ⇔ x has no prime factors other than 2 and 5.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long x;
    cin >> x;

    // Remove all factors of 2
    while (x % 2 == 0) {
        x /= 2;
    }
    // Remove all factors of 5
    while (x % 5 == 0) {
        x /= 5;
    }

    // If remaining factor is 1, then only 2 and/or 5 were present
    if (x == 1) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}