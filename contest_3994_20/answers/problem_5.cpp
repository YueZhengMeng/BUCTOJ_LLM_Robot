/* 
代码头注释：
算法名称：带状态的广度优先搜索 (Stateful BFS)
关键技巧：使用位掩码表示钥匙集合，优化状态存储与转移。
主要修改标记：[FIX] 说明修改原因
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5 + 10; // 最大顶点数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // 构建邻接表
    vector<vector<int>> adj(n + 1, vector<int>());
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    // 读取顶点属性
    vector<int> a(n + 1, 0); // a[i] 表示顶点 i 的属性
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    // [FIX] 使用 unordered_map 动态存储访问状态
    // visited[u][keys] 表示从顶点 u 出发，持有钥匙集合 keys 是否已访问
    unordered_map<int, unordered_set<int>> visited;

    // BFS 初始化
    queue<pair<int, int>> q;

    // 初始状态：从顶点 1 出发，无任何钥匙
    q.emplace(1, 0);
    visited[1].insert(0);

    while (!q.empty()) {
        auto [u, keys] = q.front();
        q.pop();

        // 如果到达目标顶点 n，输出 yes 并退出
        if (u == n) {
            cout << "yes\n";
            return 0;
        }

        // 遍历当前顶点的所有邻居
        for (auto &v : adj[u]) {
            // 如果邻居是锁，检查是否持有对应的钥匙
            if (a[v] < 0) { // 锁
                int lock_id = -a[v];
                if (keys & (1 << (lock_id - 1))) { // 检查是否持有对应钥匙
                    if (visited[v].find(keys) == visited[v].end()) {
                        visited[v].insert(keys);
                        q.emplace(v, keys);
                    }
                }
            } else if (a[v] > 0) { // 钥匙
                int new_keys = keys | (1 << (a[v] - 1)); // 收集新钥匙
                if (visited[v].find(new_keys) == visited[v].end()) {
                    visited[v].insert(new_keys);
                    q.emplace(v, new_keys);
                }
            } else { // 无锁无钥匙
                if (visited[v].find(keys) == visited[v].end()) {
                    visited[v].insert(keys);
                    q.emplace(v, keys);
                }
            }
        }
    }

    // 如果无法到达目标顶点 n，输出 no
    cout << "no\n";
    return 0;
}