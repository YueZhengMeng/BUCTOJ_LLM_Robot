/* 代码头注释：说明算法名称和关键技巧 */
// 算法名称：最小生成树计数
// 关键技巧：并查集管理连通性，组合数学计算边权组合

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int MOD = 998244353;

struct DSU {
    vector<int> parent, rank;
    DSU(int n) : parent(n + 1), rank(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) swap(x, y);
        parent[y] = x;
        rank[x] += rank[y];
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, K;
    cin >> n >> K;
    vector<tuple<int, int, int>> edges(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = {w, u, v};
    }

    sort(edges.begin(), edges.end());
    DSU dsu(n);
    ll ans = 1;
    int i = 0;
    while (i < n - 1) {
        int j = i;
        while (j < n - 1 && get<0>(edges[j]) == get<0>(edges[i])) {
            ++j;
        }
        int cnt = 0;
        for (int k = i; k < j; ++k) {
            auto [w, u, v] = edges[k];
            int pu = dsu.find(u), pv = dsu.find(v);
            if (pu != pv) {
                ++cnt;
            }
        }
        if (cnt > 0) {
            auto [w, u, v] = edges[i];
            ans = ans * (K - w + 1) % MOD;
        }
        for (int k = i; k < j; ++k) {
            auto [w, u, v] = edges[k];
            dsu.unite(u, v);
        }
        i = j;
    }

    cout << ans << '\n';
    return 0;
}