/* 数字跳格 - 带状态扩展的BFS */
#include <bits/stdc++.h>
using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct State {
    int x, y;
    int mod; // step % 3
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    
    vector<vector<int>> grid(n, vector<int>(n));
    vector<vector<vector<int>>> dist(n, vector<vector<int>>(n, vector<int>(3, -1)));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }

    queue<State> q;
    q.push({0, 0, 0}); // 初始状态是第0步（尚未移动）
    dist[0][0][0] = 0;

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        
        // 到达终点
        if (curr.x == n-1 && curr.y == n-1) {
            cout << dist[curr.x][curr.y][curr.mod] << '\n';
            return 0;
        }

        // 下一步的模状态
        int next_mod = (curr.mod + 1) % 3;
        
        for (int i = 0; i < 4; ++i) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            
            int current_val = grid[curr.x][curr.y];
            int neighbor_val = grid[nx][ny];
            
            bool valid = false;
            // 根据当前步数模3决定移动规则
            switch (curr.mod) {
                case 0: // 第1步：奇数->偶数
                    valid = (current_val % 2 == 1) && (neighbor_val % 2 == 0);
                    break;
                case 1: // 第2步：偶数->奇数
                    valid = (current_val % 2 == 0) && (neighbor_val % 2 == 1);
                    break;
                case 2: // 第3步：同奇偶
                    valid = (current_val % 2) == (neighbor_val % 2);
                    break;
            }
            
            if (valid && dist[nx][ny][next_mod] == -1) {
                dist[nx][ny][next_mod] = dist[curr.x][curr.y][curr.mod] + 1;
                q.push({nx, ny, next_mod});
            }
        }
    }

    // 无法到达终点
    cout << -1 << '\n';
    return 0;
}