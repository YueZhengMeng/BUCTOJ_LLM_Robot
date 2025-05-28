/* 文件头注释：图着色问题，使用回溯算法 */
#include <bits/stdc++.h>
using namespace std;

int n, m, l;
vector<vector<int>> graph;
vector<int> colors;
int ans = 0;

// 检查当前节点是否可以涂上指定颜色
bool isSafe(int node, int color) {
    for (int neighbor : graph[node]) {
        if (colors[neighbor] == color) {
            return false;
        }
    }
    return true;
}

// 回溯函数，尝试为每个节点着色
void backtrack(int node) {
    if (node == n) {
        ans++;
        return;
    }
    for (int color = 1; color <= m; color++) {
        if (isSafe(node, color)) {
            colors[node] = color;
            backtrack(node + 1);
            colors[node] = 0; // 回溯
        }
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m >> l;
        graph.clear();
        graph.resize(n);
        colors.assign(n, 0);
        ans = 0;
        for (int i = 0; i < l; i++) {
            int u, v;
            cin >> u >> v;
            u--; v--; // 转换为0-based索引
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        backtrack(0);
        cout << ans << endl;
    }
    return 0;
}