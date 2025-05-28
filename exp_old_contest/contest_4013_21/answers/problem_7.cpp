/* 文件头注释：比较两个整数的大小，输出对应的题目 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;  // 输入两个整数a和b
    if (a > b) {
        cout << "A" << endl;  // 如果a大于b，输出A
    } else {
        cout << "B" << endl;  // 否则输出B
    }
    return 0;
}