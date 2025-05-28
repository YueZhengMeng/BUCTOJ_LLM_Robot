/* 
  Algorithm: Likelihood comparison reduces to counting equal adjacent rolls.
  We compare the count of repeats in sequences A and B; the larger one is from 小L.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> A(n), B(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < n; i++) cin >> B[i];

    int cntA = 0, cntB = 0;
    for (int i = 1; i < n; i++) {
        if (A[i] == A[i-1]) cntA++;
        if (B[i] == B[i-1]) cntB++;
    }

    // The sequence with more repeats is more likely 小L’s
    cout << (cntA > cntB ? 'A' : 'B') << "\n";
    return 0;
}