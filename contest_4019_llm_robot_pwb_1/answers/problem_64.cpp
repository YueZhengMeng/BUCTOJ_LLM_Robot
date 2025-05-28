/* 文件头注释：使用哈希集合找出不是两个数组共有的元素 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M;
    while (cin >> N) {
        vector<int> arr1(N);
        for (int i = 0; i < N; ++i) {
            cin >> arr1[i];
        }
        cin >> M;
        vector<int> arr2(M);
        for (int i = 0; i < M; ++i) {
            cin >> arr2[i];
        }
        
        unordered_set<int> set1(arr1.begin(), arr1.end());
        unordered_set<int> set2(arr2.begin(), arr2.end());
        
        vector<int> result;
        // 找出在arr1中但不在arr2中的元素
        for (int num : arr1) {
            if (set2.find(num) == set2.end()) {
                result.push_back(num);
                set2.insert(num); // 防止重复输出
            }
        }
        // 找出在arr2中但不在arr1中的元素
        for (int num : arr2) {
            if (set1.find(num) == set1.end()) {
                result.push_back(num);
                set1.insert(num); // 防止重复输出
            }
        }
        
        // 输出结果
        for (size_t i = 0; i < result.size(); ++i) {
            if (i > 0) cout << " ";
            cout << result[i];
        }
        cout << endl;
    }
    return 0;
}