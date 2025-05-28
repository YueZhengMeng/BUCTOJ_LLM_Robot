/* 文件头注释：使用Tarjan算法寻找强连通分量，并通过拓扑排序计算最大权值路径 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 2e5 + 5;

vector<pair<int, int>> adj[MAXN]; // 邻接表，存储图
vector<int> scc[MAXN]; // 存储每个强连通分量的节点
int scc_id[MAXN]; // 记录每个节点所属的强连通分量
int scc_cnt = 0; // 强连通分量的数量
int low[MAXN], dfn[MAXN], time_stamp = 0;
stack<int> stk;
bool in_stack[MAXN];
ll scc_max[MAXN]; // 每个强连通分量的最大权值
ll dp[MAXN]; // 用于拓扑排序的DP数组

void tarjan(int u) {
    low[u] = dfn[u] = ++time_stamp;
    stk.push(u);
    in_stack[u] = true;
    for (auto &edge : adj[u]) {
        int v = edge.first;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        scc_cnt++;
        while (true) {
            int v = stk.top();
            stk.pop();
            in_stack[v] = false;
            scc_id[v] = scc_cnt;
            scc[scc_cnt].push_back(v);
            if (v == u) break;
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<ll> c(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> c[i];
    }
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }

    // 使用Tarjan算法寻找强连通分量
    for (int i = 1; i <= N; ++i) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    // 计算每个强连通分量的最大权值
    for (int i = 1; i <= scc_cnt; ++i) {
        ll max_val = 0;
        for (int u : scc[i]) {
            max_val += c[u];
            for (auto &edge : adj[u]) {
                int v = edge.first;
                if (scc_id[v] == i) {
                    max_val += edge.second;
                }
            }
        }
        scc_max[i] = max_val;
    }

    // 构建强连通分量之间的图
    vector<vector<int>> scc_adj(scc_cnt + 1);
    vector<int> in_degree(scc_cnt + 1, 0);
    for (int u = 1; u <= N; ++u) {
        for (auto &edge : adj[u]) {
            int v = edge.first;
            if (scc_id[u] != scc_id[v]) {
                scc_adj[scc_id[u]].push_back(scc_id[v]);
                in_degree[scc_id[v]]++;
            }
        }
    }

    // 拓扑排序并计算最大权值路径
    queue<int> q;
    for (int i = 1; i <= scc_cnt; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
        dp[i] = scc_max[i];
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : scc_adj[u]) {
            dp[v] = max(dp[v], dp[u] + scc_max[v]);
            if (--in_degree[v] == 0) {
                q.push(v);
            }
        }
    }

    // 输出最大权值
    ll ans = 0;
    for (int i = 1; i <= scc_cnt; ++i) {
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;

    return 0;
}