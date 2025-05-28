/* 文件头注释：核心算法为矩阵遍历与对角线处理 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> garden(n, vector<int>(n));
    
    // 读取花圃数据
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> garden[i][j];
        }
    }
    
    // 找到两条对角线上的植物高度
    vector<int> diagonalHeights;
    for (int i = 0; i < n; ++i) {
        diagonalHeights.push_back(garden[i][i]); // 主对角线
        diagonalHeights.push_back(garden[i][n - 1 - i]); // 副对角线
    }
    
    // 找到最矮的植物高度
    int minHeight = *min_element(diagonalHeights.begin(), diagonalHeights.end());
    
    // 计算卖出的美元总数
    int totalMoney = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j || i + j == n - 1) {
                // 对角线上的植物，计算与最小高度的差值
                totalMoney += (garden[i][j] - minHeight) * 2;
            } else {
                // 非对角线上的植物，全部铲光
                totalMoney += garden[i][j] * 2;
            }
        }
    }
    
    cout << totalMoney << endl;
    return 0;
}