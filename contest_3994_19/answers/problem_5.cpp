/* 
  算法：带等待列表的BFS动态解锁
  关键技巧：遇锁阻塞记录，获钥批量释放
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int MAXN = 200000 + 5;
constexpr int MAXM = 400000 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
int head[MAXN], to[MAXM], nxt[MAXM], ecnt = 0;
int a[MAXN];
bool visited[MAXN];
bool keyObtained[MAXN];
vector<int> waitList[MAXN];
int q[MAXN], ql = 0, qr = 0;

// 添加无向边  // DEBUG
void addEdge(int u, int v) {
    to[ecnt] = v;
    nxt[ecnt] = head[u];
    head[u] = ecnt++;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读入
    cin >> n >> m;
    // 初始化邻接表
    for (int i = 1; i <= n; i++) head[i] = -1;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        addEdge(x, y);
        addEdge(y, x);
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // BFS 初始化
    visited[1] = true;
    q[qr++] = 1;

    // 核心 BFS + 动态解锁处理
    while (ql < qr) {
        int u = q[ql++];

        // 获得钥匙后，释放所有等待此锁的节点  // DEBUG
        if (a[u] > 0) {
            int k = a[u];
            if (!keyObtained[k]) {
                keyObtained[k] = true;
                for (int v : waitList[k]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q[qr++] = v;
                    }
                }
                waitList[k].clear();
            }
        }
        if (u == n) break;

        // 遍历邻居
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (visited[v]) continue;
            // 遇锁阻塞，否则直接入队  // DEBUG
            if (a[v] < 0) {
                int lockId = -a[v];
                if (keyObtained[lockId]) {
                    visited[v] = true;
                    q[qr++] = v;
                } else {
                    waitList[lockId].push_back(v);
                }
            } else {
                visited[v] = true;
                q[qr++] = v;
            }
        }
    }

    // 输出结果
    cout << (visited[n] ? "yes" : "no") << "\n";
    return 0;
}