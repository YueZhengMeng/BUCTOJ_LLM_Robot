/* 文件头注释：单位矩阵初始化，使用双重循环遍历矩阵 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;  // 输入矩阵的行数

    // 初始化n*n的矩阵
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // 判断是否在主对角线上
            if (i == j) {
                cout << "1 ";
            } else {
                cout << "0 ";
            }
        }
        cout << endl;  // 每行输出完毕后换行
    }

    return 0;
}