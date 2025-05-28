/* 
  Multiplication Sign Shift
  Brute-force all possible splits of the concatenated digits (excluding original split)
  and compare products.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string S;
        cin >> S;
        int origPos = S.find('*');
        // Extract original operands
        string A = S.substr(0, origPos);
        string B = S.substr(origPos + 1);
        // Compute original product using 128-bit to be safe
        __int128 a = 0, b = 0;
        for (char c : A) a = a * 10 + (c - '0');
        for (char c : B) b = b * 10 + (c - '0');
        __int128 target = a * b;

        // Build concatenated digit string
        string Tstr = A + B;
        int N = (int)Tstr.size();
        bool possible = false;

        // Try every new split position
        for (int i = 1; i < N; i++) {
            if (i == (int)A.size()) continue;  // Skip original split
            // Left part [0..i-1], right part [i..N-1]
            // Parse to integers
            __int128 x = 0, y = 0;
            for (int j = 0; j < i; j++) {
                x = x * 10 + (Tstr[j] - '0');
            }
            for (int j = i; j < N; j++) {
                y = y * 10 + (Tstr[j] - '0');
            }
            if (x * y == target) {
                possible = true;
                break;
            }
        }

        cout << (possible ? "Yes\n" : "No\n");
    }
    return 0;
}