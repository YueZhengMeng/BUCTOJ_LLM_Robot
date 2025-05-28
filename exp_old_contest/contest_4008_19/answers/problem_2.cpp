/* 
  Problem C: 最短等差子序列
  Key insight: a recursive odd‐then‐even permutation avoids any 3‐term AP subsequence,
  so the longest AP‐subsequence length can always be kept at 2 for all n>=2.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;
    // For any n >= 2, one can construct a permutation with no 3‐term AP subsequence.
    // Hence the longest AP subsequence has length exactly 2.
    cout << 2 << "\n";
    return 0;
}