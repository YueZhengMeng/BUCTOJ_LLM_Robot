/* 
   Algorithm: Bitwise iterative addition 
   Key idea: sum = x ^ y, carry = (x & y) << 1, repeat until carry is zero.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long x, y;
    cin >> x >> y;

    // Iteratively apply binary addition via bitwise ops until no carry remains
    while (y != 0) {
        long long sum = x ^ y;           // bitwise sum without carry
        long long carry = (x & y) << 1;  // carry bits shifted
        x = sum;
        y = carry;
    }

    cout << x << "\n";
    return 0;
}