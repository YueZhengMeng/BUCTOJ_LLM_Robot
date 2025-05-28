/* 文件头注释：矩阵转置算法，关键技术为行列索引互换 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int matrix[3][3];
    
    // 输入3x3矩阵
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> matrix[i][j];
        }
    }
    
    // 转置矩阵
    for (int i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    
    // 输出转置后的矩阵
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}