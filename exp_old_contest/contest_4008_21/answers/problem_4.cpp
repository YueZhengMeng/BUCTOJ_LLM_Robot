/* 文件头注释：核心算法为动态规划与状态预处理，关键技术为快速区间查询 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    string balloons;
    cin >> balloons;
    int Q;
    cin >> Q;
    
    // 预处理每个位置的状态
    int n = balloons.size();
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    
    // 初始化单个气球的状态
    for (int i = 0; i < n; ++i) {
        dp[i][i] = (balloons[i] == 'R');
    }
    
    // 动态规划预处理所有区间
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            // 情况1：直接拿走两个相邻且颜色相同的气球
            for (int k = i; k < j; ++k) {
                if (dp[i][k] && dp[k+1][j]) {
                    dp[i][j] = true;
                    break;
                }
            }
            // 情况2：用台下两个不同颜色的气球替换
            if (!dp[i][j]) {
                for (int k = i; k < j; ++k) {
                    // [FIX] 增加所有可能的替换组合判断
                    if ((dp[i][k] && balloons[k+1] == 'R') || 
                        (dp[k+1][j] && balloons[i] == 'R') ||
                        (balloons[i] == 'G' && balloons[j] == 'B') ||
                        (balloons[i] == 'B' && balloons[j] == 'G') ||
                        (balloons[i] == 'R' && balloons[j] == 'G') ||
                        (balloons[i] == 'G' && balloons[j] == 'R') ||
                        (balloons[i] == 'R' && balloons[j] == 'B') ||
                        (balloons[i] == 'B' && balloons[j] == 'R')) {
                        dp[i][j] = true;
                        break;
                    }
                }
            }
            // [FIX] 特别处理区间长度为2的情况
            if (len == 2 && !dp[i][j]) {
                char a = balloons[i], b = balloons[j];
                if ((a == 'G' && b == 'B') || (a == 'B' && b == 'G') ||
                    (a == 'R' && b == 'G') || (a == 'G' && b == 'R') ||
                    (a == 'R' && b == 'B') || (a == 'B' && b == 'R')) {
                    dp[i][j] = true;
                }
            }
        }
    }
    
    // 处理每个查询
    string result;
    for (int q = 0; q < Q; ++q) {
        int L, R;
        cin >> L >> R;
        // 转换为0-based索引
        int l = L - 1, r = R - 1;
        result += (dp[l][r] ? 'Y' : 'N');
    }
    
    cout << result << endl;
    return 0;
}