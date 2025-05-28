/* 文件头注释：计算由数字2重复组成的数列的和 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;  // 输入n
    int sum = 0;  // 初始化总和
    int current = 0;  // 当前生成的数

    for (int i = 1; i <= n; ++i) {
        current = current * 10 + 2;  // 生成下一个数，如2, 22, 222等
        sum += current;  // 累加到总和中
    }

    cout << sum << endl;  // 输出结果
    return 0;
}