/* 算法名称：二维差分数组 + 二维前缀和
   关键技巧：使用差分数组记录区域更新，最后通过前缀和计算每个格子的最终状态 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
constexpr int MAXN = 1005;

int diff[MAXN][MAXN];  // 二维差分数组

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    // 初始化差分数组
    memset(diff, 0, sizeof(diff));

    // 处理每个操作
    for (int i = 0; i < k; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        // 更新差分数组
        diff[x1][y1] ^= 1;
        diff[x1][y2+1] ^= 1;
        diff[x2+1][y1] ^= 1;
        diff[x2+1][y2+1] ^= 1;
    }

    // 计算前缀和得到最终状态
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            diff[i][j] ^= diff[i-1][j] ^ diff[i][j-1] ^ diff[i-1][j-1];
            cout << diff[i][j];
        }
        cout << '\n';
    }

    return 0;
}