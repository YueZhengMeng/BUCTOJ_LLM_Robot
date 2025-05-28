/* 代码头注释：最长上升子序列（LIS）问题，使用二分查找优化解法 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> dp; // dp[i] 表示长度为 i+1 的上升子序列的最小末尾元素
    for (int i = 0; i < n; ++i) {
        // 使用二分查找找到第一个大于等于 a[i] 的位置
        auto it = lower_bound(dp.begin(), dp.end(), a[i]);
        if (it == dp.end()) {
            dp.push_back(a[i]); // 如果找不到，说明可以延长当前最长子序列
        } else {
            *it = a[i]; // 否则更新该位置的值
        }
    }

    cout << dp.size() << endl; // 输出最长上升子序列的长度
    return 0;
}