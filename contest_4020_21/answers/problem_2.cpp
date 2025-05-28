/* 幸运印章问题：数学最优解计算 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;
    
    if (n == 1) {
        cout << 4 << endl;
        return 0;
    }
    
    // 修正后的公式：
    // 1. 基础需求：4n个半圆（2n个印章）
    // 2. 最大节省：每共享一条边节省1个印章（2半圆）
    // 3. 最优排列下可共享2*(sqrt(n)-1)条边
    // 最终公式：4n - 2*(sqrt(n)-1) - 1 = 4n - 2*sqrt(n) + 1
    long long ans = 4 * n - 2 * (long long)sqrt(n) + 1;
    
    cout << ans << endl;
    return 0;
}