/* 文件头注释：图像转换为Transformer输入token序列 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    // 读取三个通道的矩阵
    vector<vector<int>> red(n, vector<int>(m));
    vector<vector<int>> green(n, vector<int>(m));
    vector<vector<int>> blue(n, vector<int>(m));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> red[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> green[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> blue[i][j];
        }
    }
    
    // 切块并求和
    int block_size = 4;
    int new_n = n / block_size;
    int new_m = m / block_size;
    vector<vector<int>> token(new_n * new_m, vector<int>(3, 0));
    
    for (int i = 0; i < new_n; ++i) {
        for (int j = 0; j < new_m; ++j) {
            int sum_red = 0, sum_green = 0, sum_blue = 0;
            for (int x = 0; x < block_size; ++x) {
                for (int y = 0; y < block_size; ++y) {
                    sum_red += red[i * block_size + x][j * block_size + y];
                    sum_green += green[i * block_size + x][j * block_size + y];
                    sum_blue += blue[i * block_size + x][j * block_size + y];
                }
            }
            token[i * new_m + j][0] = sum_red;
            token[i * new_m + j][1] = sum_green;
            token[i * new_m + j][2] = sum_blue;
        }
    }
    
    // [FIX] 直接使用原始token矩阵，不进行转置
    // 拼接特殊token
    vector<vector<int>> final_token(new_n * new_m + 1, vector<int>(3));
    for (int i = 0; i < new_n * new_m; ++i) {
        for (int j = 0; j < 3; ++j) {
            final_token[i][j] = token[i][j];
        }
    }
    // [FIX] 修正特殊token的值为(l,x,r)的ASCII码
    final_token[new_n * new_m][0] = 108;  // 'l'
    final_token[new_n * new_m][1] = 120;  // 'x'
    final_token[new_n * new_m][2] = 114;  // 'r'
    
    // 输出结果
    for (int i = 0; i < final_token.size(); ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << final_token[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}