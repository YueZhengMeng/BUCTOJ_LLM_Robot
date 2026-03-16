/* 扑克牌比较：直接比较两个整数并输出结果 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;                // 读取两个点数
    if (a > b)                    // A的点数更大
        cout << "A" << endl;
    else if (a < b)               // B的点数更大
        cout << "B" << endl;
    else                          // 点数相同
        cout << "=" << endl;
    return 0;
}