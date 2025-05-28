/* 文件头注释：模拟博弈过程，贪心策略 */
#include <bits/stdc++.h>
using namespace std;

// 找到PolarBear的最佳涂色位置
int find_best_cell(const vector<int>& cells) {
    int best_cell = -1;
    int min_valid = INT_MAX;
    
    for (int i = 0; i < cells.size(); ++i) {
        if (cells[i] == 0) {
            bool is_valid = true;
            // 检查相邻格子是否有红色
            if (i > 0 && cells[i-1] == 1) is_valid = false;
            if (i < cells.size()-1 && cells[i+1] == 1) is_valid = false;
            if (is_valid) {
                // 模拟涂色后的状态
                vector<int> new_cells = cells;
                new_cells[i] = 1;
                // 计算涂色后的有效格子数
                int valid_count = 0;
                for (int j = 0; j < new_cells.size(); ++j) {
                    if (new_cells[j] == 0) {
                        bool is_valid_new = true;
                        if (j > 0 && new_cells[j-1] == 1) is_valid_new = false;
                        if (j < new_cells.size()-1 && new_cells[j+1] == 1) is_valid_new = false;
                        if (is_valid_new) valid_count++;
                    }
                }
                // 选择有效格子数最小的位置
                if (valid_count < min_valid) {
                    min_valid = valid_count;
                    best_cell = i;
                }
            }
        }
    }
    
    return best_cell;
}

int main() {
    int n;
    cin >> n;
    
    // 初始化单元格状态，0表示白色，1表示红色
    vector<int> cells(n, 0);
    
    int dongdziz_score = 0;
    int turn = 0; // 0表示dongdziz的回合，1表示PolarBear的回合
    
    while (true) {
        bool has_valid_cell = false;
        int leftmost_valid = -1;
        
        // 寻找最左边的有效格子
        for (int i = 0; i < n; ++i) {
            if (cells[i] == 0) {
                bool is_valid = true;
                // 检查相邻格子是否有红色
                if (i > 0 && cells[i-1] == 1) is_valid = false;
                if (i < n-1 && cells[i+1] == 1) is_valid = false;
                if (is_valid) {
                    has_valid_cell = true;
                    leftmost_valid = i;
                    break;
                }
            }
        }
        
        if (!has_valid_cell) break; // 没有有效格子，游戏结束
        
        if (turn == 0) {
            // dongdziz的回合，涂最左边的有效格子
            cells[leftmost_valid] = 1;
            dongdziz_score++;
        } else {
            // PolarBear的回合，涂最佳位置
            int best_cell = find_best_cell(cells);
            if (best_cell != -1) {
                cells[best_cell] = 1;
            }
        }
        
        turn = 1 - turn; // 切换回合
    }
    
    cout << dongdziz_score << endl;
    return 0;
}