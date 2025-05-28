/* 文件头注释：计算3x3矩阵的主对角线和副对角线元素之和 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int matrix[3][3];
    
    // 输入矩阵
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> matrix[i][j];
        }
    }
    
    // 计算主对角线和
    int mainDiagonalSum = 0;
    for (int i = 0; i < 3; ++i) {
        mainDiagonalSum += matrix[i][i];
    }
    
    // 计算副对角线和
    int secondaryDiagonalSum = 0;
    for (int i = 0; i < 3; ++i) {
        secondaryDiagonalSum += matrix[i][2 - i];
    }
    
    // 输出结果
    cout << mainDiagonalSum << " " << secondaryDiagonalSum << endl;
    
    return 0;
}