/* 文件头注释：使用Kruskal算法求解最小生成树问题 */
#include <bits/stdc++.h>
using namespace std;

// 并查集数据结构
struct UnionFind {
    vector<int> parent, rank;
    UnionFind(int n) : parent(n), rank(n, 1) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int u) {
        if (parent[u] != u) parent[u] = find(parent[u]);
        return parent[u];
    }
    void unite(int u, int v) {
        int pu = find(u), pv = find(v);
        if (pu == pv) return;
        if (rank[pu] < rank[pv]) swap(pu, pv);
        parent[pv] = pu;
        if (rank[pu] == rank[pv]) ++rank[pu];
    }
};

// 边的结构体
struct Edge {
    int u, v, cost;
    bool operator<(const Edge& other) const {
        return cost < other.cost;
    }
};

int main() {
    int n;
    while (cin >> n && n != 0) {
        vector<Edge> edges;
        // 读取输入并构建边列表
        for (int i = 0; i < n - 1; ++i) {
            char u;
            int k;
            cin >> u >> k;
            for (int j = 0; j < k; ++j) {
                char v;
                int cost;
                cin >> v >> cost;
                edges.push_back({u - 'A', v - 'A', cost});
            }
        }
        // 按边权从小到大排序
        sort(edges.begin(), edges.end());
        UnionFind uf(n);
        int total_cost = 0;
        // Kruskal算法构建最小生成树
        for (const Edge& e : edges) {
            if (uf.find(e.u) != uf.find(e.v)) {
                uf.unite(e.u, e.v);
                total_cost += e.cost;
            }
        }
        cout << total_cost << endl;
    }
    return 0;
}