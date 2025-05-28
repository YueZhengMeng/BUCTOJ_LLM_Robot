/* 文件头注释：核心算法为贪心策略，模拟僵尸对抗过程 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> enemy_hp(n);
    for (int i = 0; i < n; ++i) {
        cin >> enemy_hp[i];
    }

    queue<int> ally_queue; // 己方僵尸队列
    int charm_count = 0; // 魅惑菇使用次数

    for (int i = 0; i < n; ++i) {
        if (!ally_queue.empty()) {
            if (ally_queue.front() > enemy_hp[i]) {
                // 己方僵尸健康度大于敌方僵尸，直接对抗
                ally_queue.front() -= enemy_hp[i];
            } else if (ally_queue.front() == enemy_hp[i]) {
                // 健康度相等，同时消失
                ally_queue.pop();
            } else {
                // 己方僵尸健康度小于敌方僵尸，己方僵尸消失，敌方僵尸健康度减少
                enemy_hp[i] -= ally_queue.front();
                ally_queue.pop();
                // 重新检查是否可以使用魅惑菇
                if (i < n - 1 && (ally_queue.empty() || ally_queue.front() <= enemy_hp[i])) {
                    ally_queue.push(enemy_hp[i]);
                    charm_count++;
                }
            }
        } else {
            // 使用魅惑菇，将敌方僵尸转化为己方僵尸
            ally_queue.push(enemy_hp[i]);
            charm_count++;
        }
    }

    cout << charm_count << endl;
    return 0;
}