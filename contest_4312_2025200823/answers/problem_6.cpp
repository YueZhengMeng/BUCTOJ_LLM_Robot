/* 
 * Gomoku Winning Move Checker
 * Algorithm: Enumerate all empty cells, simulate placing a stone, and check
 *            four directions for five consecutive stones of the player's color.
 */
#include <bits/stdc++.h>
using namespace std;

// Direction vectors: horizontal, vertical, diagonal \, diagonal /
const int dx[4] = {0, 1, 1, 1};
const int dy[4] = {1, 0, 1, -1};

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, c;
        cin >> n >> c;
        vector<string> board(n);
        for (int i = 0; i < n; i++) {
            cin >> board[i];
        }

        // If board is too small, impossible to have five in a row
        if (n < 5) {
            cout << "NO" << endl;
            continue;
        }

        char player = c + '0';  // player's stone as character
        bool canWin = false;

        // Iterate over all cells
        for (int i = 0; i < n && !canWin; i++) {
            for (int j = 0; j < n && !canWin; j++) {
                if (board[i][j] != '0') continue;  // not empty

                // Check each of the four directions
                for (int dir = 0; dir < 4; dir++) {
                    int count = 1;  // include the current placement

                    // Positive direction
                    int x = i + dx[dir], y = j + dy[dir];
                    while (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == player) {
                        count++;
                        x += dx[dir];
                        y += dy[dir];
                    }

                    // Negative direction
                    x = i - dx[dir], y = j - dy[dir];
                    while (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == player) {
                        count++;
                        x -= dx[dir];
                        y -= dy[dir];
                    }

                    if (count >= 5) {
                        canWin = true;
                        break;
                    }
                }
            }
        }

        cout << (canWin ? "YES" : "NO") << endl;
    }
    return 0;
}