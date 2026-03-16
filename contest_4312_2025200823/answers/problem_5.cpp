/* 复数乘法：根据公式 (a+bi)(c+di) = (ac-bd) + (ad+bc)i */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int real = a * c - b * d;
    int imag = a * d + b * c;
    cout << real << " " << imag << endl;
    return 0;
}