/* 
  Algorithm: Greedy two-pointer on sorted arrays 
  to maximize the number of pairs (a_i, b_j) with a_i > b_j.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int i = 0, j = 0, wins = 0;
    // Two-pointer scan
    while (i < n && j < n) {
        if (a[i] > b[j]) {
            // a[i] can beat b[j]
            wins++;
            i++;
            j++;
        } else {
            // a[i] too small, try next a[i]
            i++;
        }
    }

    cout << wins << "\n";
    return 0;
}