/* 文件头注释：拓扑排序算法解决标签球问题 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        vector<vector<int>> adj(N + 1);
        vector<int> inDegree(N + 1, 0);
        
        for (int i = 0; i < M; ++i) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            inDegree[b]++;
        }
        
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int i = 1; i <= N; ++i) {
            if (inDegree[i] == 0) {
                pq.push(i);
            }
        }
        
        vector<int> weight(N + 1);
        int currentWeight = 1;
        bool hasSolution = true;
        
        while (!pq.empty()) {
            int u = pq.top();
            pq.pop();
            weight[u] = currentWeight++;
            
            for (int v : adj[u]) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    pq.push(v);
                }
            }
        }
        
        if (currentWeight != N + 1) {
            hasSolution = false;
        }
        
        if (!hasSolution) {
            cout << -1 << endl;
        } else {
            for (int i = 1; i <= N; ++i) {
                cout << weight[i] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}