/* 文件头注释：判断1/x是否为有限小数，核心算法为质因数分解 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int x;
    cin >> x;
    
    // 不断除以2，直到不能整除
    while (x % 2 == 0) {
        x /= 2;
    }
    
    // 不断除以5，直到不能整除
    while (x % 5 == 0) {
        x /= 5;
    }
    
    // 如果x最终变为1，说明质因数只包含2和5，输出YES
    if (x == 1) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    
    return 0;
}