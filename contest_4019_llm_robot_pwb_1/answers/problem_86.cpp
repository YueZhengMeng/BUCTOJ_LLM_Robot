/* 文件头注释：使用双堆（最大堆和最小堆）来动态维护第i小的元素 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    vector<int> a(m), u(n);
    for (int i = 0; i < m; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> u[i];
    
    priority_queue<int> maxHeap; // 存储当前最小的i个元素
    priority_queue<int, vector<int>, greater<int>> minHeap; // 存储剩余的元素
    
    int i = 0, idx = 0;
    for (int j = 0; j < m; ++j) {
        if (!maxHeap.empty() && a[j] < maxHeap.top()) {
            maxHeap.push(a[j]);
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else {
            minHeap.push(a[j]);
        }
        
        while (idx < n && u[idx] == j + 1) {
            i++;
            maxHeap.push(minHeap.top());
            minHeap.pop();
            cout << maxHeap.top() << endl;
            idx++;
        }
    }
    
    return 0;
}