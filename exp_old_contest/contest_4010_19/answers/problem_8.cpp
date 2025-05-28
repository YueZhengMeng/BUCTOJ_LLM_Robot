/* 
   2-Finger Typing on QWERTY Keyboard
   - Build adjacency on a 2D embedding of the QWERTY letter keys.
   - Precompute all-pairs shortest paths by BFS.
   - DP over (left_pos, right_pos) states for each character in the string.
*/
#include <bits/stdc++.h>
using namespace std;
static const int INF = 1000000000;
int distKey[26][26];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // 1) Map each letter to a 2D coordinate (approximate QWERTY layout)
    vector<pair<double,double>> pos(26);
    string row0 = "qwertyuiop";
    string row1 = "asdfghjkl";
    string row2 = "zxcvbnm";
    for(int i=0;i<10;i++)
        pos[row0[i]-'a'] = {double(i), 0.0};
    for(int i=0;i<9;i++)
        pos[row1[i]-'a'] = {double(i) + 0.5, 1.0};
    for(int i=0;i<7;i++)
        pos[row2[i]-'a'] = {double(i) + 1.0, 2.0};

    // 2) Build adjacency: any two letters within Δx≤1 and Δy≤1 are neighbors
    vector<vector<int>> adj(26);
    for(int u=0;u<26;u++){
        for(int v=u+1;v<26;v++){
            double dx = fabs(pos[u].first  - pos[v].first);
            double dy = fabs(pos[u].second - pos[v].second);
            if(dx <= 1.0 + 1e-9 && dy <= 1.0 + 1e-9){
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
        }
    }

    // 3) Precompute all-pairs shortest paths by BFS
    for(int src=0; src<26; src++){
        for(int j=0;j<26;j++) distKey[src][j] = INF;
        deque<int> dq;
        distKey[src][src] = 0;
        dq.push_back(src);
        while(!dq.empty()){
            int u = dq.front(); dq.pop_front();
            for(int v: adj[u]){
                if(distKey[src][v] > distKey[src][u] + 1){
                    distKey[src][v] = distKey[src][u] + 1;
                    dq.push_back(v);
                }
            }
        }
    }

    int T;
    cin >> T;
    // dp arrays: 26 x 26 states
    static int dp[26][26], dp2[26][26];
    char startL = 'f', startR = 'j';
    int sL = startL - 'a', sR = startR - 'a';

    while(T--){
        string S;
        cin >> S;
        // initialize dp to INF
        for(int i=0;i<26;i++)
            for(int j=0;j<26;j++)
                dp[i][j] = INF;
        dp[sL][sR] = 0;

        // process each character
        for(char ch : S){
            int c = ch - 'a';
            // reset dp2
            for(int i=0;i<26;i++)
                for(int j=0;j<26;j++)
                    dp2[i][j] = INF;

            // transition
            for(int x=0;x<26;x++){
                for(int y=0;y<26;y++){
                    int cur = dp[x][y];
                    if(cur == INF) continue;
                    // move left finger x->c
                    int costL = cur + distKey[x][c];
                    if(costL < dp2[c][y])
                        dp2[c][y] = costL;
                    // move right finger y->c
                    int costR = cur + distKey[y][c];
                    if(costR < dp2[x][c])
                        dp2[x][c] = costR;
                }
            }
            // swap dp and dp2
            for(int i=0;i<26;i++)
                for(int j=0;j<26;j++)
                    dp[i][j] = dp2[i][j];
        }

        // answer = min over all end states
        int ans = INF;
        for(int i=0;i<26;i++)
            for(int j=0;j<26;j++)
                ans = min(ans, dp[i][j]);
        cout << ans << "\n";
    }
    return 0;
}