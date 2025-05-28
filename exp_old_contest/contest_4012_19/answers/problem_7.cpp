/* 
   Inverse Gray Code
   Technique: repeated XOR with right-shift to recover the original integer from its Gray code.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        uint32_t y;
        cin >> y;
        // Invert Gray code: x = y ^ (y>>1) ^ (y>>2) ^ ... as needed
        uint32_t x = y;
        x ^= x >> 1;
        x ^= x >> 2;
        x ^= x >> 4;
        x ^= x >> 8;
        x ^= x >> 16;
        cout << x << "\n";
    }
    return 0;
}