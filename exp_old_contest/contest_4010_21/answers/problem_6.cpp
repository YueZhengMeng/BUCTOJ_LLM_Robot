/* 文件头注释：使用优先队列维护最小的k个前缀和 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M, k;
    cin >> N >> M >> k;
    vector<vector<int>> matrix(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> matrix[i][j];
        }
        sort(matrix[i].begin(), matrix[i].end()); // 对每行排序，方便后续处理
    }

    // 使用优先队列存储前缀和及其对应的前缀序列的最后一个元素
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // 小顶堆，用于维护最小的k个前缀和
    for (int num : matrix[0]) {
        pq.push({num, num});
    }

    for (int i = 1; i < N; ++i) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> new_pq;
        while (!pq.empty()) {
            auto [sum, last] = pq.top(); pq.pop();
            for (int num : matrix[i]) {
                if (num > last) {
                    new_pq.push({sum + num, num});
                }
            }
        }
        // 只保留最小的k个前缀和
        while (new_pq.size() > k) {
            new_pq.pop();
        }
        pq = new_pq;
    }

    vector<int> result;
    while (!pq.empty()) {
        result.push_back(pq.top().first);
        pq.pop();
    }
    sort(result.begin(), result.end());
    cout << result[k - 1] << endl;

    return 0;
}