/* 文件头注释：使用并查集维护图的连通性，动态处理顶点被雪覆盖的情况 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;

int parent[MAXN];
bool isCovered[MAXN]; // 记录顶点是否被雪覆盖
bool hasCovered[MAXN]; // 记录连通分量中是否包含被雪覆盖的顶点

// 并查集的查找操作
int find(int u) {
    if (parent[u] != u) {
        parent[u] = find(parent[u]);
    }
    return parent[u];
}

// 并查集的合并操作
void unite(int u, int v) {
    int pu = find(u);
    int pv = find(v);
    if (pu != pv) {
        parent[pu] = pv;
        hasCovered[pv] = hasCovered[pv] || hasCovered[pu]; // 合并时更新hasCovered状态
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    // 初始化并查集
    for (int i = 1; i <= N; ++i) {
        parent[i] = i;
        hasCovered[i] = false; // 初始时没有顶点被雪覆盖
    }

    // 读取边并合并连通分量
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        unite(u, v);
    }

    int Q;
    cin >> Q;

    while (Q--) {
        int type, u, v;
        cin >> type;
        if (type == 1) {
            cin >> u;
            isCovered[u] = true;
            int pu = find(u);
            hasCovered[pu] = true; // 更新连通分量的hasCovered状态
        } else {
            cin >> u >> v;
            int pu = find(u);
            int pv = find(v);
            if (pu == pv) {
                if (hasCovered[pu]) {
                    // 如果连通分量中包含被雪覆盖的顶点，则u和v都必须未被雪覆盖
                    if (!isCovered[u] && !isCovered[v]) {
                        cout << "Yes\n";
                    } else {
                        cout << "No\n";
                    }
                } else {
                    // 如果连通分量中不包含被雪覆盖的顶点，则可以直接到达
                    cout << "Yes\n";
                }
            } else {
                // 如果u和v不在同一个连通分量中，则无法到达
                cout << "No\n";
            }
        }
    }

    return 0;
}