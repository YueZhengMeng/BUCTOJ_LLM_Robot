/* 文件头注释：使用BFS算法探索棋盘状态转换 */
#include <bits/stdc++.h>
using namespace std;

// 将4x4棋盘的状态编码为一个16位的整数
int encode(const vector<vector<int>>& board) {
    int state = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            state |= board[i][j] << (i * 4 + j);
        }
    }
    return state;
}

// 将16位的整数解码为4x4棋盘的状态
vector<vector<int>> decode(int state) {
    vector<vector<int>> board(4, vector<int>(4));
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            board[i][j] = (state >> (i * 4 + j)) & 1;
        }
    }
    return board;
}

// 翻转一行
int flipRow(int state, int row) {
    for (int j = 0; j < 4; ++j) {
        state ^= 1 << (row * 4 + j);
    }
    return state;
}

// 翻转一列
int flipCol(int state, int col) {
    for (int i = 0; i < 4; ++i) {
        state ^= 1 << (i * 4 + col);
    }
    return state;
}

// 翻转一个2x2的正方形
int flipSquare(int state, int x, int y) {
    for (int i = x; i < x + 2; ++i) {
        for (int j = y; j < y + 2; ++j) {
            state ^= 1 << (i * 4 + j);
        }
    }
    return state;
}

int main() {
    vector<vector<int>> A(4, vector<int>(4));
    vector<vector<int>> B(4, vector<int>(4));
    
    // 读取初始状态A
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> A[i][j];
        }
    }
    
    // 读取目标状态B
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> B[i][j];
        }
    }
    
    int start = encode(A);
    int target = encode(B);
    
    if (start == target) {
        cout << "Yes" << endl;
        return 0;
    }
    
    queue<int> q;
    q.push(start);
    
    unordered_set<int> visited;
    visited.insert(start);
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        // 尝试所有可能的翻转操作
        for (int i = 0; i < 4; ++i) {
            int next = flipRow(current, i);
            if (next == target) {
                cout << "Yes" << endl;
                return 0;
            }
            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                q.push(next);
            }
        }
        
        for (int j = 0; j < 4; ++j) {
            int next = flipCol(current, j);
            if (next == target) {
                cout << "Yes" << endl;
                return 0;
            }
            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                q.push(next);
            }
        }
        
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                int next = flipSquare(current, i, j);
                if (next == target) {
                    cout << "Yes" << endl;
                    return 0;
                }
                if (visited.find(next) == visited.end()) {
                    visited.insert(next);
                    q.push(next);
                }
            }
        }
    }
    
    cout << "No" << endl;
    return 0;
}