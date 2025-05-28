/* 
  Algorithm: Offline dynamic connectivity via DSU in reverse time.
  Key technique: Each edge (u,v) is “deleted” when both endpoints are snowed.
  In reverse, we add edges in decreasing event-time, answering connectivity queries.
*/
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, sz;
    DSU(int n): p(n+1), sz(n+1,1) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a,b);
        p[b] = a;
        sz[a] += sz[b];
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<pair<int,int>> edges(M);
    for(int i = 0; i < M; i++){
        cin >> edges[i].first >> edges[i].second;
    }
    int Q; 
    cin >> Q;
    // Store events: type 1 u; type 2 u v
    struct Event { int type, u, v; };
    vector<Event> ev(Q+1);
    // Record snowing time for each vertex (default Q+1 = never snowed)
    vector<int> snow_time(N+1, Q+1);

    for(int i = 1; i <= Q; i++){
        cin >> ev[i].type;
        if(ev[i].type == 1){
            cin >> ev[i].u;
            snow_time[ev[i].u] = i;  // vertex u snowed at time i
        } else {
            cin >> ev[i].u >> ev[i].v;
        }
    }

    // Bucket edges by the time they become disabled = max(snow_time[u], snow_time[v])
    vector<vector<pair<int,int>>> add_edges(Q+2);
    for(auto &e: edges){
        int u = e.first, v = e.second;
        int t = max(snow_time[u], snow_time[v]);
        // t in [1..Q] => edge is deleted at time t; in reverse, we add at step t
        // t = Q+1 => never deleted, add before reversal
        add_edges[t].emplace_back(u, v);
    }

    // DSU init; add all edges with t = Q+1 (never deleted)
    DSU dsu(N);
    for(auto &e: add_edges[Q+1]){
        dsu.unite(e.first, e.second);
    }

    vector<string> answers;
    answers.reserve(Q);

    // Process events in reverse
    for(int t = Q; t >= 1; t--){
        if(ev[t].type == 2){
            // Connectivity query in reversed-time graph
            int u = ev[t].u, v = ev[t].v;
            answers.push_back( dsu.find(u) == dsu.find(v) ? "Yes" : "No" );
        } else {
            // Event was snowing of u; in reverse we un-snow and add edges disabled at t
            for(auto &e: add_edges[t]){
                dsu.unite(e.first, e.second);
            }
        }
    }

    // Reverse answers back to original order and output
    for(int i = (int)answers.size()-1; i >= 0; i--){
        cout << answers[i] << "\n";
    }
    return 0;
}