#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 输入数据
    constexpr int n = 5;
    int In[n] = {1, 0, 1, 0, 1};

    // DP数组，dp[i][j]表示第i行第j个圆形的可能值
    vector<unordered_set<int>> dp(n);
    for (int i = 0; i < n; ++i) {
        dp[i].insert(In[i]);
    }

    // 动态规划计算
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            unordered_set<int> newSet;
            for (int a : dp[i-1][j]) {
                for (int b : dp[i-1][j+1]) {
                    newSet.insert(a & b); // 与门
                    newSet.insert(a | b); // 或门
                    newSet.insert(a ^ b); // 异或门
                }
            }
            dp[i][j] = newSet;
        }
    }

    // 统计最终输出为1的组合数
    int count = 0;
    for (int val : dp[n-1][0]) {
        if (val == 1) {
            ++count;
        }
    }

    cout << count << endl;

    return 0;
}