/* 文件头注释：通过计算连续相同点数的次数来判断哪个序列是小L掷出的 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> A(n), B(n);
    for (int i = 0; i < n; ++i) cin >> A[i];
    for (int i = 0; i < n; ++i) cin >> B[i];

    // 计算序列A中连续相同点数的次数
    int countA = 0;
    for (int i = 1; i < n; ++i) {
        if (A[i] == A[i-1]) {
            countA++;
        }
    }

    // 计算序列B中连续相同点数的次数
    int countB = 0;
    for (int i = 1; i < n; ++i) {
        if (B[i] == B[i-1]) {
            countB++;
        }
    }

    // 比较两个序列的连续相同点数次数，输出结果
    if (countA > countB) {
        cout << "A" << endl;
    } else {
        cout << "B" << endl;
    }

    return 0;
}