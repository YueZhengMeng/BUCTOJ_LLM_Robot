/* 
  Conversion between Holocene (Human Era) and Gregorian calendar.
  For HE > 10000: AD (HE - 10000)
  For HE ≤ 10000: BC (10001 - HE)
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x;
    cin >> x;
    if (x > 10000) {
        // AD era
        cout << "AD " << (x - 10000) << "\n";
    } else {
        // BC era, note the absence of year zero in Gregorian
        cout << (10001 - x) << " BC\n";
    }
    return 0;
}