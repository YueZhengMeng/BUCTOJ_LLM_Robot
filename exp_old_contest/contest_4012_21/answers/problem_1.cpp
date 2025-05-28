/* 文件头注释：动态规划解决军队人数问题 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, L, R;
    cin >> n >> L >> R;
    
    // 初始化dp数组，dp[i]表示是否可以达到人数i
    vector<bool> dp(R + 1, false);
    dp[1] = true;  // 初始军队人数为1
    
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        
        // 临时数组，用于存储更新后的dp状态
        vector<bool> new_dp(R + 1, false);
        
        for (int j = 1; j <= R; ++j) {
            if (dp[j]) {
                if (j + x <= R) new_dp[j + x] = true;
                if (j + y <= R) new_dp[j + y] = true;
            }
        }
        
        // 更新dp数组
        dp = new_dp;
    }
    
    // 检查是否有一个人数在[L, R]范围内
    for (int i = L; i <= R; ++i) {
        if (dp[i]) {
            cout << "Yes" << endl;
            return 0;
        }
    }
    
    cout << "No" << endl;
    return 0;
}