/* 文件头注释：使用Dijkstra算法求解地铁网络中的最短路径 */
#include <bits/stdc++.h>
using namespace std;

// 定义站点和线路的结构
unordered_map<string, vector<pair<string, int>>> graph; // 邻接表表示图
unordered_map<string, int> dist; // 存储每个站点的最短距离
unordered_map<string, unordered_set<int>> stationToLines; // 记录每个站点所属的线路

void dijkstra(const string& start) {
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    pq.push({0, start});
    dist[start] = 0;

    while (!pq.empty()) {
        auto [current_dist, u] = pq.top();
        pq.pop();

        if (current_dist > dist[u]) continue;

        for (auto& [v, weight] : graph[u]) {
            if (dist.find(v) == dist.end() || dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }

        // 动态添加换乘边
        for (int line : stationToLines[u]) {
            for (const string& neighbor : graph[u]) {
                if (stationToLines[neighbor.first].count(line) == 0) {
                    for (int otherLine : stationToLines[neighbor.first]) {
                        if (otherLine != line) {
                            graph[u].emplace_back(neighbor.first, Y);
                            graph[neighbor.first].emplace_back(u, Y);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int n, X, Y;
    cin >> n >> X >> Y;

    // 读取地铁线路
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        vector<string> stations(k);
        for (int j = 0; j < k; ++j) {
            cin >> stations[j];
            stationToLines[stations[j]].insert(i);
        }

        // 添加相邻站点之间的边
        for (int j = 0; j < k - 1; ++j) {
            graph[stations[j]].emplace_back(stations[j + 1], X);
            graph[stations[j + 1]].emplace_back(stations[j], X);
        }
    }

    string start, end;
    cin >> start >> end;

    // 使用Dijkstra算法计算最短路径
    dijkstra(start);

    // 输出结果
    cout << dist[end] << endl;

    return 0;
}