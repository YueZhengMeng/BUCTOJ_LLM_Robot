/* 
   Problem: 简简单单解方程
   Technique: Direct algebraic solution of two-variable linear equations
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int A, B;
    cin >> A >> B;
    // Compute x and y using derived formulas
    int x = (A + B) / 2;
    int y = (A - B) / 2;
    cout << x << " " << y << "\n";
    return 0;
}