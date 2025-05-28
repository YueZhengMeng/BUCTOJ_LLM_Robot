#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
constexpr int MAXN = 200010;

vector<int> adj[MAXN]; // 邻接表存储树结构
int color[MAXN];       // 存储每个节点的颜色
int cnt[MAXN];         // 用于统计颜色频率
int ans = 0;           // 记录颜色平衡子树的数量

void dfs(int u, unordered_map<int, int>& colorCount) {
    colorCount[color[u]]++; // 统计当前节点的颜色
    for (int v : adj[u]) {
        unordered_map<int, int> childColorCount;
        dfs(v, childColorCount);
        // 合并子树的颜色统计
        for (auto& [col, cnt] : childColorCount) {
            colorCount[col] += cnt;
        }
    }
    // 检查当前子树是否为颜色平衡树
    if (!colorCount.empty()) {
        int first = colorCount.begin()->second;
        bool balanced = true;
        for (auto& [col, cnt] : colorCount) {
            if (cnt != first) {
                balanced = false;
                break;
            }
        }
        if (balanced) ans++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int c, f;
        cin >> c >> f;
        color[i] = c;
        if (f != 0) adj[f].push_back(i);
    }

    unordered_map<int, int> colorCount;
    dfs(1, colorCount);

    cout << ans << "\n";
    return 0;
}