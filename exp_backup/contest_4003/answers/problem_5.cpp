/* 代码头注释：说明算法名称和关键技巧 */
// 算法名称：计数图的最小生成树
// 关键技巧：Kruskal 算法的逆向思维，组合数学，并查集优化

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

vector<int> parent, rank_;

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        if (rank_[x] < rank_[y]) {
            swap(x, y);
        }
        parent[y] = x;
        if (rank_[x] == rank_[y]) {
            rank_[x]++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, K;
    cin >> n >> K;
    vector<Edge> edges(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    // 按边权排序
    sort(edges.begin(), edges.end());

    // 初始化并查集
    parent.resize(n + 1);
    rank_.resize(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
    }

    ll result = 1;
    int i = 0;
    while (i < n - 1) {
        int current_weight = edges[i].w;
        vector<Edge> same_weight_edges;
        while (i < n - 1 && edges[i].w == current_weight) {
            same_weight_edges.push_back(edges[i]);
            i++;
        }

        // 第一步：统计可以加入最小生成树的边数（树边）
        int cnt = 0;
        for (const auto& edge : same_weight_edges) {
            if (find(edge.u) != find(edge.v)) {
                cnt++;
            }
        }

        // 第二步：更新并查集
        for (const auto& edge : same_weight_edges) {
            if (find(edge.u) != find(edge.v)) {
                unite(edge.u, edge.v);
            }
        }

        // 第三步：统计非树边数量（连接已连通节点的边）
        int non_tree_edges = 0;
        for (const auto& edge : same_weight_edges) {
            if (find(edge.u) == find(edge.v)) {
                non_tree_edges++;
            }
        }

        // 第四步：计算贡献
        result = result * (K - current_weight + 1) % MOD;  // 树边贡献
        result = result * (1LL << non_tree_edges) % MOD;  // 非树边贡献
    }

    cout << result << endl;

    return 0;
}