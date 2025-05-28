/* 文件头注释：使用数组存储输入，逆序输出 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    const int N = 10;  // 定义常量N为10
    int nums[N];       // 定义数组存储输入的10个整数

    // 输入10个整数
    for (int i = 0; i < N; ++i) {
        cin >> nums[i];
    }

    // 逆序输出
    for (int i = N - 1; i >= 0; --i) {
        cout << nums[i];
        if (i > 0) {
            cout << " ";  // 数字之间用空格分隔
        }
    }
    cout << endl;  // 输出换行符

    return 0;
}