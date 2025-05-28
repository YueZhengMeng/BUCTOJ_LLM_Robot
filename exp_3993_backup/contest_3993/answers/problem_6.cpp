/* 代码头注释：树形DP解决没有上司的舞会问题
   关键技巧：状态转移方程、邻接表存储树结构、递归实现 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
constexpr int MAXN = 6005;

int N;
int H[MAXN];
vector<int> adj[MAXN];
int dp[MAXN][2];

void dfs(int u, int parent) {
    dp[u][0] = 0; // 不选u
    dp[u][1] = H[u]; // 选u
    for (int v : adj[u]) {
        if (v == parent) continue;
        dfs(v, u);
        dp[u][0] += max(dp[v][0], dp[v][1]); // 不选u时，子节点可选可不选
        dp[u][1] += dp[v][0]; // 选u时，子节点不能选
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 1; i <= N; ++i) {
        cin >> H[i];
    }
    for (int i = 1; i < N; ++i) {
        int L, K;
        cin >> L >> K;
        adj[K].push_back(L);
        adj[L].push_back(K);
    }
    int root = 1; // 假设根节点为1
    dfs(root, -1);
    cout << max(dp[root][0], dp[root][1]) << endl;

    return 0;
}