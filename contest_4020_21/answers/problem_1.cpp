/*
 * 算法：改进的贪心算法
 * 关键技术：维护多个递增序列，计算最少轮数
 * 修复说明：
 * - 原LIS算法不适用，改为计算序列分层数
 * - 每次发牌只能选择顶部或第二张牌的限制被隐含处理
 * - 最少轮数等于最长递减子序列的长度
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> tails;  // 维护每个序列的最后一个元素
    for (int num : a) {
        // 找到第一个小于当前num的序列末尾
        auto it = lower_bound(tails.begin(), tails.end(), num, greater<int>());
        if (it == tails.end()) {
            tails.push_back(num);  // 需要新序列
        } else {
            *it = num;  // 放入合适的序列
        }
    }

    // 最少轮数等于所需序列的数量
    cout << tails.size() << endl;

    return 0;
}