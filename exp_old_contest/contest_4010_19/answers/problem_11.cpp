/* 
  PolarBear's Coloring Game
  Key observation: under optimal defense, Dong's picks occur at positions 1,5,9,...
  Total picks = ceil(n/4).
*/
#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin >> n)) return 0;

    // [FIX] 使用动态规划替代不准确的 (n+3)/4 公式
    vector<int> dp(n+1, 0);
    dp[0] = 0;
    for(int len = 1; len <= n; len++){
        int L = len - 2;
        if(L <= 0){
            // 只有一轮 Dongdziz 涂第1格
            dp[len] = 1;
        } else {
            int best = INT_MAX;
            // PolarBear 在剩余长度 L 中选奇数位置 j
            for(int j = 1; j <= L; j += 2){
                int left_len  = j - 2;
                int right_len = L - j - 1;
                int left_dp  = (left_len  > 0 ? dp[left_len]  : 0);
                int right_dp = (right_len > 0 ? dp[right_len] : 0);
                best = min(best, left_dp + right_dp);
            }
            dp[len] = 1 + best;
        }
    }

    cout << dp[n] << "\n";
    return 0;
}