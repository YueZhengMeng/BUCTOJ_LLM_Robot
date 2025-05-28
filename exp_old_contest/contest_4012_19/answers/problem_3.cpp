/* 
  Algorithm: Sliding Window (Two Pointers)
  Maintains a window [left, right] with at most m zeros, tracking the max length.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;

    int left = 0;
    int zeroCount = 0;
    int maxCombo = 0;

    for (int right = 0; right < n; ++right) {
        // If we include s[right] and it's '0', increase zeroCount
        if (s[right] == '0') {
            ++zeroCount;
        }
        // Shrink from the left until we have at most m zeros in the window
        while (zeroCount > m) {
            if (s[left] == '0') {
                --zeroCount;
            }
            ++left;
        }
        // Update max length of valid window
        maxCombo = max(maxCombo, right - left + 1);
    }

    cout << maxCombo << "\n";
    return 0;
}