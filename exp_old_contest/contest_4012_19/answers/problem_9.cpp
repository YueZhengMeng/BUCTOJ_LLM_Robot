/* 
  Algorithm: Dijkstra on expanded graph
  - station-line nodes for each appearance (ride cost X)
  - station hub nodes for transfers (cost Y)
  - super-source/sink for start/end
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (ll)1e18;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int X, Y;
    cin >> n >> X >> Y;

    // Read lines, map station-name -> station-id
    unordered_map<string,int> stMap;
    stMap.reserve(300000);
    vector<vector<int>> lines(n);
    int stationCnt = 0;
    ll totalAppear = 0;
    for(int i = 0; i < n; i++){
        int k; 
        cin >> k;
        lines[i].resize(k);
        totalAppear += k;
        for(int j = 0; j < k; j++){
            string s; 
            cin >> s;
            auto it = stMap.find(s);
            if(it == stMap.end()){
                stMap[s] = stationCnt;
                lines[i][j] = stationCnt++;
            } else {
                lines[i][j] = it->second;
            }
        }
    }
    string St, Ed;
    cin >> St >> Ed;
    int sId = stMap[St], eId = stMap[Ed];

    int M = (int)totalAppear;           // number of station-line nodes
    int hubOff = M;                     // station-hub nodes start here
    int SRC = M + stationCnt;           // super-source
    int SINK = SRC + 1;                 // super-sink
    int Nnode = SINK + 1;

    // adjacency list: (neighbor, weight)
    vector<vector<pair<int,int>>> adj(Nnode);

    // For recording all appearances of a station
    vector<vector<int>> occ(stationCnt);
    occ.reserve(stationCnt);

    // Build graph
    int sl_idx = 0;  // index of current station-line node
    for(int i = 0; i < n; i++){
        auto &ln = lines[i];
        int k = ln.size();
        for(int j = 0; j < k; j++){
            int sid = ln[j];
            int nodeSL = sl_idx++;
            occ[sid].push_back(nodeSL);
            // transfer edges via station-hub
            int hub = hubOff + sid;
            adj[nodeSL].emplace_back(hub, Y);  // pay Y to go to hub
            adj[hub].emplace_back(nodeSL, 0);  // exit hub for free

            // ride edges on same line
            if(j > 0){
                int prevSL = nodeSL - 1;
                adj[nodeSL].emplace_back(prevSL, X);
                adj[prevSL].emplace_back(nodeSL, X);
            }
        }
    }

    // source -> all appearances of St (cost 0)
    for(int nodeSL: occ[sId]){
        adj[SRC].emplace_back(nodeSL, 0);
    }
    // all appearances of Ed -> sink (cost 0)
    for(int nodeSL: occ[eId]){
        adj[nodeSL].emplace_back(SINK, 0);
    }

    // Dijkstra from SRC to SINK
    vector<ll> dist(Nnode, INF);
    dist[SRC] = 0;
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    pq.emplace(0, SRC);

    while(!pq.empty()){
        auto [d,u] = pq.top(); 
        pq.pop();
        if(d > dist[u]) continue;
        if(u == SINK) break;
        for(auto &e: adj[u]){
            int v = e.first, w = e.second;
            ll nd = d + w;
            if(nd < dist[v]){
                dist[v] = nd;
                pq.emplace(nd, v);
            }
        }
    }

    cout << dist[SINK] << "\n";
    return 0;
}