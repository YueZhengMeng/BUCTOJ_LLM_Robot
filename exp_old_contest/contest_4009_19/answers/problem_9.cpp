/* 
  Algorithm: 
    1) Tarjan's SCC to contract strongly connected components.
    2) Sum node‐weights and internal edge‐weights per SCC.
    3) Build condensation DAG with inter‐component edges.
    4) Topological‐order DP to find maximum collectible treasure.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static const int MAXN = 200000;

int N, M;
vector<pair<int,ll>> adj[MAXN+1];
int dfn[MAXN+1], low[MAXN+1], compId[MAXN+1];
bool inStack[MAXN+1];
int dfsTime = 0, compCount = 0;
stack<int> st;
ll nodeVal[MAXN+1];

// Tarjan's DFS
void tarjan(int u) {
    dfn[u] = low[u] = ++dfsTime;
    st.push(u);  inStack[u] = true;
    for (auto &pr : adj[u]) {
        int v = pr.first;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        ++compCount;
        while (true) {
            int x = st.top(); st.pop();
            inStack[x] = false;
            compId[x] = compCount;
            if (x == u) break;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for(int i = 1; i <= N; i++){
        cin >> nodeVal[i];
    }
    // read edges
    struct Edge { int u, v; ll w; };
    vector<Edge> edges(M);
    for(int i = 0; i < M; i++){
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        adj[edges[i].u].push_back({edges[i].v, edges[i].w});
    }
    // 1) Run Tarjan to find SCCs
    for(int i = 1; i <= N; i++){
        if (!dfn[i]) tarjan(i);
    }
    // 2) Accumulate component values
    vector<ll> compVal(compCount+1, 0);
    for(int i = 1; i <= N; i++){
        compVal[compId[i]] += nodeVal[i];
    }
    // 3) Build DAG of components and add internal edge weights
    vector<vector<pair<int,ll>>> dag(compCount+1);
    vector<int> indeg(compCount+1, 0);
    for(auto &e : edges){
        int cu = compId[e.u], cv = compId[e.v];
        if (cu == cv) {
            // internal edge in SCC
            compVal[cu] += e.w;
        } else {
            // inter-SCC edge
            dag[cu].push_back({cv, e.w});
            indeg[cv]++;
        }
    }
    // 4) Topo-order DP
    vector<ll> dp(compCount+1, 0);
    for(int i = 1; i <= compCount; i++){
        dp[i] = compVal[i];
    }
    queue<int> q;
    for(int i = 1; i <= compCount; i++){
        if (indeg[i] == 0) q.push(i);
    }
    ll answer = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        answer = max(answer, dp[u]);
        for (auto &ed : dag[u]) {
            int v = ed.first;
            ll w = ed.second;
            // Transition: take dp[u], then edge w, then compVal[v]
            dp[v] = max(dp[v], dp[u] + w + compVal[v]);
            if (--indeg[v] == 0) {
                q.push(v);
            }
        }
    }
    cout << answer << "\n";
    return 0;
}