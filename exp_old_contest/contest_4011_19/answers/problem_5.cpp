/* 
   Algorithm: Direct computation of distance to nearest multiple of 5 
   Key technique: modulus and simple min comparison 
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    // r = remainder when dividing by 5
    int r = t % 5;
    // Minimum distance to either the previous multiple of 5 or the next
    int result = min(r, 5 - r);
    cout << result << "\n";
    return 0;
}