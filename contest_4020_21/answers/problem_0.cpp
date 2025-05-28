/* 子集和的平方的奇偶性判断
   关键点：统计奇数个数，判断其与n的关系 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    int odd_count = 0;
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        if (num % 2 != 0) ++odd_count;
    }
    
    if (odd_count == 0) {
        // 所有子集和都是偶数
        cout << "Even\n";
    } else {
        // 奇数子集数为2^{n-1}，当n>1时为偶数
        if (n == 1) {
            cout << "Odd\n";
        } else {
            cout << "Even\n";
        }
    }
    
    return 0;
}