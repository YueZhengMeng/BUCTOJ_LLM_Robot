/* 
  Problem A: Subset sum of squares parity
  Key idea: Expand (sum_T a_i)^2, take mod 2, only singleton contributions remain
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    // Read elements but only the first matters if n==1
    if (n == 1) {
        long long x;
        cin >> x;
        // S = x^2, parity = x mod 2
        cout << (x % 2 ? "Odd" : "Even");
    } else {
        // For n >= 2, 2^{n-1} factor makes S even
        // consume input
        for (int i = 0; i < n; i++) {
            int tmp;
            cin >> tmp;
        }
        cout << "Even";
    }
    return 0;
}