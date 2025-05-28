/* 文件头注释：使用欧几里得算法计算最大公约数，进而求出最少参赛队数 */
#include <bits/stdc++.h>
using namespace std;

// 计算最大公约数的函数
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int K;
    cin >> K; // 读取计算用例数
    while (K--) {
        int m, n;
        cin >> m >> n; // 读取两校的报名人数
        int g = gcd(m, n); // 计算最大公约数
        int teams = (m / g) + (n / g); // 计算最少参赛队数
        cout << teams << endl; // 输出结果
    }
    return 0;
}