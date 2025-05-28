/* 文件头注释：二维数组最大值及位置查找 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    // 定义一个3x4的矩阵
    int matrix[3][4];
    
    // 从键盘输入12个数字填充矩阵
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> matrix[i][j];
        }
    }
    
    // 初始化最大值及其位置
    int max_value = matrix[0][0];
    int max_row = 0, max_col = 0;
    
    // 遍历矩阵，寻找最大值及其位置
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (matrix[i][j] > max_value) {
                max_value = matrix[i][j];
                max_row = i;
                max_col = j;
            }
        }
    }
    
    // 输出最大值及其位置
    cout << max_value << " " << max_row << " " << max_col << endl;
    
    return 0;
}