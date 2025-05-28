/* 算法名称：动态规划
   关键技巧：记录以某个数字结尾的最长接龙序列长度 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    // 记录以某个数字结尾的最长接龙序列长度
    int dp[10] = {0};  // 0-9 分别代表数字的末位
    for (int i = 0; i < N; ++i) {
        int num = A[i];
        int firstDigit = to_string(num)[0] - '0';
        int lastDigit = num % 10;
        dp[lastDigit] = max(dp[lastDigit], dp[firstDigit] + 1);
    }

    // 找到最长的接龙序列长度
    int maxLen = 0;
    for (int i = 0; i < 10; ++i) {
        maxLen = max(maxLen, dp[i]);
    }

    // 输出需要删除的元素个数
    cout << N - maxLen << endl;

    return 0;
}