/* 文件头注释：判断素数的函数，使用试除法 */
#include <bits/stdc++.h>
using namespace std;

// 判断是否为素数的函数
bool isPrime(int n) {
    if (n <= 1) return false; // 1和负数不是素数
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false; // 如果n能被i整除，则n不是素数
    }
    return true; // 否则n是素数
}

int main() {
    int n;
    cin >> n; // 输入整数
    if (isPrime(n)) {
        cout << "prime" << endl; // 如果是素数，输出prime
    } else {
        cout << "not prime" << endl; // 如果不是素数，输出not prime
    }
    return 0;
}