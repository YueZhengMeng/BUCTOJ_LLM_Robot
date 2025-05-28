/* 文件头注释：动态规划求解最大LCM问题 */
/* 主要修改标记：[FIX] 采用动态规划策略，优化LCM计算 */
#include <bits/stdc++.h>
using namespace std;

// 计算最大公约数
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 计算最小公倍数
int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

int main() {
    int N;
    cin >> N;

    // DP数组，记录每个和值对应的最大LCM值
    vector<int> dp(N + 1, 1);
    // 回溯数组，记录每个和值对应的最后一个数
    vector<int> last(N + 1, 1);

    // 动态规划求解
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= i; ++j) {
            int current_lcm = lcm(dp[i - j], j);
            if (current_lcm > dp[i]) {
                dp[i] = current_lcm;
                last[i] = j;
            }
        }
    }

    // 回溯得到分解方式
    vector<int> result;
    int remaining = N;
    while (remaining > 0) {
        result.push_back(last[remaining]);
        remaining -= last[remaining];
    }

    // 输出字典序最小的解
    sort(result.begin(), result.end());
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}