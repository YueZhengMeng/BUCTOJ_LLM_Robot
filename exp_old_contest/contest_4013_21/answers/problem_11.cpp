/* 文件头注释：实现递归定义的二元函数 sigma(x, y) */
#include <bits/stdc++.h>
using namespace std;

// 递归计算 sigma(x, y)
int sigma(int x, int y) {
    if (y == 0) {
        return x;
    }
    return sigma(x ^ y, 2 * (x & y));
}

int main() {
    int x, y;
    cin >> x >> y;
    cout << sigma(x, y) << endl;
    return 0;
}