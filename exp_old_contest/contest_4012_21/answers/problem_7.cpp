/* 文件头注释：核心算法为逐位确定x的值，关键技术为位运算 */
#include <bits/stdc++.h>
using namespace std;

int findX(int y) {
    int x = 0;
    for (int i = 0; i <= 31; ++i) {
        // 通过y的第i位和x的第i-1位确定x的第i位
        int bit = (y >> i) & 1;
        int prevBit = (i > 0) ? ((x >> (i - 1)) & 1) : 0;
        x |= (bit ^ prevBit) << i;
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int y;
        cin >> y;
        cout << findX(y) << '\n';
    }

    return 0;
}