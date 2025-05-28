/* 文件头注释：核心算法为数学公式计算伤害，关键技术为预处理和快速查询 */
#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;

int main() {
    int n, m, k, q;
    cin >> n >> m >> k >> q;
    
    // 记录每行的豌豆射手位置
    vector<vector<int>> shooters(6);
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        shooters[x].push_back(y);
    }
    
    // 记录每行的火炬树桩位置
    vector<vector<int>> torches(6);
    for (int i = 0; i < k; ++i) {
        int x, y;
        cin >> x >> y;
        torches[x].push_back(y);
    }
    
    // 预处理每行的火炬树桩位置，方便快速查询
    for (int i = 1; i <= 5; ++i) {
        sort(torches[i].begin(), torches[i].end());
    }
    
    // 处理每个询问
    for (int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        long long damage = 0;
        
        // 遍历该行的所有豌豆射手
        for (int shooterY : shooters[x]) {
            if (shooterY >= y) continue; // 豌豆射手在僵尸右侧，无法攻击
            int distance = y - shooterY;
            int baseDamage = distance; // 基础伤害为距离
            int torchCount = 0;
            
            // 计算火炬树桩对伤害的加成
            auto it = lower_bound(torches[x].begin(), torches[x].end(), shooterY);
            while (it != torches[x].end() && *it < y) {
                torchCount++;
                ++it;
            }
            
            baseDamage += 2 * torchCount; // 每个火炬树桩增加2点伤害
            damage = (damage + baseDamage) % MOD;
        }
        
        cout << damage << endl;
    }
    
    return 0;
}