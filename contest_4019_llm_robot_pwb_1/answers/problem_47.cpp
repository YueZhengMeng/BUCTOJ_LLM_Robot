/* 文件头注释：归并排序中的合并算法 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int K;
    cin >> K;
    while (K--) {
        int n, m;
        cin >> n;
        vector<int> A(n);
        for (int i = 0; i < n; ++i) {
            cin >> A[i];
        }
        cin >> m;
        vector<int> B(m);
        for (int i = 0; i < m; ++i) {
            cin >> B[i];
        }
        
        // 输出A班队员的身高顺序
        for (int i = 0; i < n; ++i) {
            cout << A[i] << " ";
        }
        cout << endl;
        
        // 输出B班队员的身高顺序
        for (int i = 0; i < m; ++i) {
            cout << B[i] << " ";
        }
        cout << endl;
        
        // 合并两个有序队列
        vector<int> merged;
        int i = 0, j = 0;
        while (i < n && j < m) {
            if (A[i] < B[j]) {
                merged.push_back(A[i++]);
            } else {
                merged.push_back(B[j++]);
            }
        }
        while (i < n) {
            merged.push_back(A[i++]);
        }
        while (j < m) {
            merged.push_back(B[j++]);
        }
        
        // 输出混合队列的身高顺序
        for (int k = 0; k < merged.size(); ++k) {
            cout << merged[k] << " ";
        }
        cout << endl;
    }
    return 0;
}