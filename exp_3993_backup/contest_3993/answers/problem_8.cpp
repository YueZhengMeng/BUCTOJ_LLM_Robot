/* 代码头注释：拓扑排序 + 动态规划计算期望路径长度 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
const int MAXN = 100010;  // 最大节点数
const int MAXM = 200010;  // 最大边数

int N, M;
vector<pair<int, int>> G[MAXN];  // 邻接表，存储 (目标节点, 边长度)
int outDegree[MAXN];             // 每个节点的出度
int inDegree[MAXN];              // 每个节点的入度
double E[MAXN];                  // 期望路径长度

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 输入
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        G[a].emplace_back(b, c);
        outDegree[a]++;
        inDegree[b]++;  // 统计入度
    }

    // 初始化期望值
    fill(E, E + MAXN, 0.0);
    // [FIX] 显式设置终点节点的期望值为0
    for (int i = 1; i <= N; i++) {
        if (outDegree[i] == 0) {
            E[i] = 0.0;
        }
    }

    // 拓扑排序
    queue<int> q;
    for (int i = 1; i <= N; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    // 动态规划计算期望值
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        // [FIX] 修改期望值计算逻辑
        if (outDegree[u] > 0) {  // 处理非终点节点
            double sum = 0.0;
            for (auto [v, c] : G[u]) {
                sum += (c + E[v]);
            }
            E[u] = sum / outDegree[u];
        }

        // 更新邻接节点的入度
        for (auto [v, c] : G[u]) {
            inDegree[v]--;
            if (inDegree[v] == 0) {
                q.push(v);
            }
        }
    }

    // 输出结果，保留两位小数
    cout << fixed << setprecision(2) << E[1] << endl;

    return 0;
}