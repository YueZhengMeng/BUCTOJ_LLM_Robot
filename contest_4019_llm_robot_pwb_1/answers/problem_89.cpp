/* 文件头注释：N皇后问题的回溯算法实现 */
#include <bits/stdc++.h>
using namespace std;

int totalSolutions = 0; // 记录总的合法放置数量

// 检查在row行col列放置皇后是否合法
bool isSafe(int row, int col, vector<int>& position) {
    for (int i = 0; i < row; ++i) {
        // 检查同一列或对角线是否有冲突
        if (position[i] == col || abs(position[i] - col) == abs(i - row)) {
            return false;
        }
    }
    return true;
}

// 回溯函数，尝试在每一行放置皇后
void solveNQueens(int row, int n, vector<int>& position) {
    if (row == n) {
        // 找到一个合法解，增加计数
        totalSolutions++;
        return;
    }
    for (int col = 0; col < n; ++col) {
        if (isSafe(row, col, position)) {
            position[row] = col; // 在row行col列放置皇后
            solveNQueens(row + 1, n, position); // 递归处理下一行
        }
    }
}

int main() {
    int n;
    while (cin >> n && n != 0) {
        totalSolutions = 0; // 重置计数器
        vector<int> position(n); // 记录每行皇后的列位置
        solveNQueens(0, n, position); // 从第0行开始回溯
        cout << totalSolutions << endl; // 输出当前N的合法解数量
    }
    return 0;
}