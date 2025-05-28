/* 代码头注释：数位DP算法，用于计算1到N之间恰好包含K个非零数字的整数的数目 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;

// 数位DP函数
ll dp[105][4][2]; // dp[pos][cnt][limit]
string num;
int K;

ll dfs(int pos, int cnt, bool limit) {
    if (pos == num.size()) return cnt == K;
    if (dp[pos][cnt][limit] != -1) return dp[pos][cnt][limit];
    ll res = 0;
    int up = limit ? num[pos] - '0' : 9;
    for (int i = 0; i <= up; ++i) {
        int new_cnt = cnt + (i != 0);
        if (new_cnt > K) continue;
        res += dfs(pos + 1, new_cnt, limit && (i == up));
    }
    return dp[pos][cnt][limit] = res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> num >> K;
    memset(dp, -1, sizeof(dp));
    cout << dfs(0, 0, true) << endl;
    return 0;
}