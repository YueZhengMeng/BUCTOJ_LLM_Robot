/* 文件头注释：核心算法为检查2x2区域对角线高度之和是否相等，并验证全局一致性 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> h(N, vector<int>(M));
    
    // 读取雪地高度
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> h[i][j];
        }
    }
    
    // 检查所有2x2区域的对角线高度之和是否相等
    bool canFlatten = true;
    for (int i = 0; i < N - 1; ++i) {
        for (int j = 0; j < M - 1; ++j) {
            int sum1 = h[i][j] + h[i+1][j+1];
            int sum2 = h[i][j+1] + h[i+1][j];
            if (sum1 != sum2) {
                canFlatten = false;
                break;
            }
        }
        if (!canFlatten) break;
    }
    
    // [FIX] 修改全局一致性检查，确保所有雪地高度的奇偶性与第一个位置的奇偶性一致
    if (canFlatten) {
        int parity = h[0][0] % 2; // 使用第一个位置的奇偶性作为基准
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (h[i][j] % 2 != parity) {
                    canFlatten = false;
                    break;
                }
            }
            if (!canFlatten) break;
        }
    }
    
    // 输出结果
    if (canFlatten) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    
    return 0;
}