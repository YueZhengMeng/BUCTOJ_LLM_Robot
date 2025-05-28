/* 
   Algorithm: BFS on augmented state (x, y, step_mod3)
   Technique: Layered BFS, parity checks for each move
*/
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
struct State { int x, y, r; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> a[i][j];

    // Special case: single cell
    if(n == 1) {
        cout << 0 << "\n";
        return 0;
    }

    // visited[x][y][r]: have we visited (x,y) with step_mod3 == r?
    vector<vector<array<char,3>>> visited(n, vector<array<char,3>>(n, {0,0,0}));
    vector<State> curr, next;
    curr.reserve(n*n);
    next.reserve(n*n);

    // Start at (0,0), 0 moves done => r=0
    visited[0][0][0] = 1;
    curr.push_back({0,0,0});
    int steps = 0;
    const int dx[4] = {1,-1,0,0}, dy[4] = {0,0,1,-1};
    int tx = n-1, ty = n-1;

    while(!curr.empty()) {
        next.clear();
        for(auto &st : curr) {
            int x = st.x, y = st.y, r = st.r;
            int v = a[x][y];
            // Try 4 neighbors
            for(int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                int nr = (r + 1) % 3;  // next step type
                int w = a[nx][ny];
                // Parity check based on step type
                bool ok = false;
                if(nr == 1) {           // step1: odd->even
                    ok = (v % 2 == 1 && w % 2 == 0);
                } else if(nr == 2) {    // step2: even->odd
                    ok = (v % 2 == 0 && w % 2 == 1);
                } else {                // nr==0 => step3: same parity
                    ok = ((v % 2) == (w % 2));
                }
                if(!ok || visited[nx][ny][nr]) continue;
                // Found the goal?
                if(nx == tx && ny == ty) {
                    cout << (steps + 1) << "\n";
                    return 0;
                }
                visited[nx][ny][nr] = 1;
                next.push_back({nx, ny, nr});
            }
        }
        steps++;
        curr.swap(next);
    }

    // No path found
    cout << -1 << "\n";
    return 0;
}