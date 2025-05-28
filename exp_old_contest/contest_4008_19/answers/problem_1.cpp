/* 
   DP over (dish index, capacity‐decay index, skip‐streak).
   caps[k] = floor(m * (2/3)^k), including a 0‐calorie stage at the end.
   dp[i][c][s]: max calories after i dishes,
     c = index in caps[], s = consecutive skips (0=eat last,1=one skip,2=two-or-more skips)
*/
/* 修复版本说明（保留原本的代码头注释） */
/* 主要修改标记：[FIX] 添加 0 卡阶段；[FIX] 优化不可达状态判断；[FIX] 修正 skip 一次时的 c2 计算 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll NEG_INF = -(1LL<<60);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n; 
    ll m;
    cin >> n >> m;
    vector<ll> a(n);
    for(int i = 0; i < n; i++) 
        cin >> a[i];

    // 1) Precompute capacities: caps[k] = floor(m * (2/3)^k)
    vector<ll> caps;
    {
        ll cur = m;
        while(cur > 0){
            caps.push_back(cur);
            cur = (cur * 2) / 3;
        }
        caps.push_back(0);               // [FIX] 显式添加 0 卡状态
    }
    int K = caps.size();  // 包含最后的 0 卡阶段

    // 2) DP array: dp[i][capIdx][skipStreak]
    static ll dp[105][30][3];
    for(int i = 0; i <= n; i++)
        for(int c = 0; c < K; c++)
            for(int s = 0; s < 3; s++)
                dp[i][c][s] = NEG_INF;

    // Initial: before any dish, 已连续 skip>=2 => full reset
    dp[0][0][2] = 0;

    for(int i = 0; i < n; i++){
        for(int c = 0; c < K; c++){
            for(int s = 0; s < 3; s++){
                ll val = dp[i][c][s];
                if(val == NEG_INF) continue;   // [FIX] 改为判等增强可读性

                // Option 1: Eat this dish
                {
                    int eff = (s == 2 ? 0 : c);
                    ll canEat = min(caps[eff], a[i]);
                    int c2 = min(eff + 1, K - 1);
                    int s2 = 0;
                    dp[i+1][c2][s2] = max(dp[i+1][c2][s2], val + canEat);
                }

                // Option 2: Skip this dish
                {
                    int s2 = min(s + 1, 2);
                    int c2;
                    if(s2 == 2) {
                        c2 = 0;                             // 跳过两次或更多 → 重置
                    } else if(s == 0) {
                        c2 = max(c - 1, 0);                // [FIX] 第一次跳过 → 恢复到上次吃完的指数
                    } else {
                        c2 = c;                            // 已在 skip 链上（s>=1 但 s2<2）→ 继承
                    }
                    dp[i+1][c2][s2] = max(dp[i+1][c2][s2], val);
                }
            }
        }
    }

    // Answer = best over all end-states
    ll ans = 0;
    for(int c = 0; c < K; c++){
        for(int s = 0; s < 3; s++){
            ans = max(ans, dp[n][c][s]);
        }
    }

    cout << ans << "\n";
    return 0;
}