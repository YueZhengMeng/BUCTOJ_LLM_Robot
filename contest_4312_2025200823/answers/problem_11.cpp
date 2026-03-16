/* 模拟中国象棋中马的移动，考虑蹩马腿和己方棋子阻挡 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    int x, y;
    cin >> x >> y;
    // grid记录棋子势力：-1表示无棋子，0表示对方，1表示己方
    vector<vector<int>> grid(n + 1, vector<int>(m + 1, -1));
    for (int i = 0; i < k; ++i) {
        int xx, yy, s;
        cin >> xx >> yy >> s;
        grid[xx][yy] = s;
    }

    // 四个基本方向：上、下、左、右
    vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vector<vector<bool>> reachable(n + 1, vector<bool>(m + 1, false));

    for (auto &d : dirs) {
        int dx = d.first, dy = d.second;
        int leg_x = x + dx, leg_y = y + dy;
        // 马腿位置必须在棋盘内且无棋子
        if (leg_x < 1 || leg_x > n || leg_y < 1 || leg_y > m) continue;
        if (grid[leg_x][leg_y] != -1) continue; // 有棋子则蹩马腿

        // 两个跳点：使用公式 (x+2*dx±dy, y+2*dy±dx)
        for (int sign : {-1, 1}) {
            int tx = x + 2 * dx + sign * dy;
            int ty = y + 2 * dy + sign * dx;
            if (tx >= 1 && tx <= n && ty >= 1 && ty <= m) {
                if (grid[tx][ty] != 1) { // 不是己方棋子即可达
                    reachable[tx][ty] = true;
                }
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (reachable[i][j]) ++ans;
    cout << ans << endl;

    return 0;
}