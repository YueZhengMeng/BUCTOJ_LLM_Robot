/* 文件头注释：使用DFS找到所有连通分量，并通过交换操作确保每个连通分量的大小不超过n */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> P(2 * n);
    for (int i = 0; i < 2 * n; ++i) {
        cin >> P[i];
        P[i]--; // 转换为0-based索引
    }

    vector<bool> visited(2 * n, false);
    int operations = 0;

    for (int i = 0; i < 2 * n; ++i) {
        if (!visited[i]) {
            vector<int> component;
            stack<int> stack;
            stack.push(i);
            visited[i] = true;

            while (!stack.empty()) {
                int node = stack.top();
                stack.pop();
                component.push_back(node);

                int neighbor = P[node];
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    stack.push(neighbor);
                }
            }

            if (component.size() > n) {
                operations += (component.size() - 1) / n;
            }
        }
    }

    cout << operations << endl;
    return 0;
}