/* 
   Problem: PolarBear 的二选一
   Technique: Simple conditional comparison
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int solversA, solversB;
    cin >> solversA >> solversB;

    // Output the problem with more solvers
    if (solversA > solversB) {
        cout << 'A';
    } else {
        cout << 'B';
    }
    return 0;
}