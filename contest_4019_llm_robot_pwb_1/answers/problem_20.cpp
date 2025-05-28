/* 文件头注释：计算两个整数的最大公约数和最小公倍数 */
#include <bits/stdc++.h>
using namespace std;

// 计算最大公约数（GCD）的函数
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 计算最小公倍数（LCM）的函数
int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

int main() {
    int a, b;
    cin >> a >> b;
    
    // 处理负数情况，取绝对值
    a = abs(a);
    b = abs(b);
    
    // 计算并输出结果
    cout << gcd(a, b) << " " << lcm(a, b) << endl;
    
    return 0;
}