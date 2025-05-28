/* 代码头注释：说明算法名称和关键技巧 */
// 算法名称：计数图的最小生成树
// 关键技巧：组合数学、并查集、树的结构预处理、LCA算法

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int MOD = 998244353;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

vector<vector<pair<int, int>>> adj;
vector<int> parent, depth, max_edge;
vector<vector<int>> up, max_up;

void dfs(int u, int p, int d, int w) {
    parent[u] = p;
    depth[u] = d;
    max_edge[u] = w;
    if (p != -1) {
        up[u][0] = p;
        max_up[u][0] = w;
        for (int i = 1; i < 20; ++i) {
            if (up[u][i - 1] != -1) {
                up[u][i] = up[up[u][i - 1]][i - 1];
                max_up[u][i] = max(max_up[u][i - 1], max_up[up[u][i - 1]][i - 1]);
            } else {
                up[u][i] = -1;
                int max_w = 0; // [FIX] 定义 max_w 变量并初始化为 0
                max_up[u][i] = max_w;
            }
        }
    }
    for (auto& [v, w] : adj[u]) {
        if (v != p) {
            dfs(v, u, d + 1, w);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = 19; i >= 0; --i) {
        if (up[u][i] != -1 && depth[u] - (1 << i) >= depth[v]) {
            u = up[u][i];
        }
    }
    if (u == v) return u;
    for (int i = 19; i >= 0; --i) {
        if (up[u][i] != -1 && up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

int get_max_edge(int u, int v) {
    int l = lca(u, v);
    int max_w = 0;
    for (int i = 19; i >= 0; --i) {
        if (up[u][i] != -1 && depth[u] - (1 << i) >= depth[l]) {
            max_w = max(max_w, max_up[u][i]);
            u = up[u][i];
        }
    }
    for (int i = 19; i >= 0; --i) {
        if (up[v][i] != -1 && depth[v] - (1 << i) >= depth[l]) {
            max_w = max(max_w, max_up[v][i]);
            v = up[v][i];
        }
    }
    return max_w;
}

struct DSU {
    vector<int> parent;
    DSU(int n) : parent(n + 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int u) {
        return parent[u] == u ? u : parent[u] = find(parent[u]);
    }
    void unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u != v) {
            parent[v] = u;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, K;
    cin >> n >> K;
    if (n == 1) {
        cout << 1 << '\n';
        return 0;
    }

    adj.resize(n + 1);
    parent.resize(n + 1);
    depth.resize(n + 1);
    max_edge.resize(n + 1);
    up.assign(n + 1, vector<int>(20, -1));
    max_up.assign(n + 1, vector<int>(20, 0));

    vector<Edge> edges(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        adj[edges[i].u].emplace_back(edges[i].v, edges[i].w);
        adj[edges[i].v].emplace_back(edges[i].u, edges[i].w);
    }

    dfs(1, -1, 0, 0);

    DSU dsu(n);
    sort(edges.begin(), edges.end());

    ll ans = 1;
    for (auto& e : edges) {
        int u = e.u, v = e.v, w = e.w;
        if (dsu.find(u) != dsu.find(v)) {
            dsu.unite(u, v);
        } else {
            int max_w = get_max_edge(u, v);
            if (max_w < K) {
                ans = ans * (K - max_w) % MOD;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}