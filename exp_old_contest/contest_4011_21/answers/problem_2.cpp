/* 文件头注释：使用并查集处理分组关系，通过哈希表统计『好战友』数量 */
#include <bits/stdc++.h>
using namespace std;

// 并查集类
class DSU {
public:
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    void unite(int x, int y) {
        int fx = find(x);
        int fy = find(y);
        if (fx != fy) {
            parent[fy] = fx;
        }
    }
};

int main() {
    int n, k;
    cin >> n >> k;
    
    // 记录每个同学在所有课程中的分组情况
    vector<map<int, int>> group(n + 1);
    
    for (int i = 0; i < k; ++i) {
        int m;
        cin >> m;
        DSU dsu(n);
        for (int j = 0; j < m; ++j) {
            int u, v;
            cin >> u >> v;
            dsu.unite(u, v);
        }
        // 记录当前课程的分组情况
        for (int j = 1; j <= n; ++j) {
            int root = dsu.find(j);
            group[j][i] = root;
        }
    }
    
    // 将每个同学的分组情况序列化为字符串，作为哈希表的键
    map<string, int> groupCount;
    for (int i = 1; i <= n; ++i) {
        string key;
        for (int c = 0; c < k; ++c) {
            key += to_string(group[i][c]) + ",";
        }
        groupCount[key]++;
    }
    
    // 统计每个同学的『好战友』数量
    vector<int> result(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        string key;
        for (int c = 0; c < k; ++c) {
            key += to_string(group[i][c]) + ",";
        }
        result[i] = groupCount[key];
    }
    
    // 输出结果
    for (int i = 1; i <= n; ++i) {
        cout << result[i] << " ";
    }
    cout << endl;
    
    return 0;
}