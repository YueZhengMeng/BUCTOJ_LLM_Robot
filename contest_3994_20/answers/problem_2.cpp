/* 
代码头注释：
算法名称：枚举掰分方案 + 数学优化
关键技巧：通过枚举第一次掰分的位置，结合数学公式快速计算最小不平衡值
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;  // 处理大数场景

const int INF = 0x3f3f3f3f;  // 典型竞赛常量定义

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);  // IO加速

    ll n, m;
    cin >> n >> m;

    ll total_area = n * m;  // 巧克力总面积
    if (total_area % 3 == 0) {
        // 如果总面积能被3整除，则最优解为0
        cout << 0 << "\n";
        return 0;
    }

    ll min_diff = LLONG_MAX;  // 初始化最小不平衡值

    // [FIX] 数学优化：只考虑关键掰分点，而非遍历所有可能位置
    for (ll i = 1; i <= n / 2 && i <= 1e6; ++i) {  // 枚举第一刀位置（限制范围以防止超时）
        ll area1 = i * m;                          // 第一块面积
        ll area2 = total_area - area1;             // 第二块面积
        // 第二次掰分在较大块中进行
        ll sub_area = area2 / 2;                   // 将较大块分成两部分
        vector<ll> areas = {area1, sub_area, area2 - sub_area};
        sort(areas.begin(), areas.end());
        ll current_diff = areas[2] - areas[0];     // 计算当前不平衡值
        min_diff = min(min_diff, current_diff);

        // [FIX] 提前终止条件：如果当前不平衡值已大于等于最优解，则无需继续
        if (current_diff >= min_diff) break;
    }

    // [FIX] 同理，对列方向的掰分也进行优化
    for (ll j = 1; j <= m / 2 && j <= 1e6; ++j) {  // 枚举第一刀位置（限制范围以防止超时）
        ll area1 = j * n;                          // 第一块面积
        ll area2 = total_area - area1;             // 第二块面积
        // 第二次掰分在较大块中进行
        ll sub_area = area2 / 2;                   // 将较大块分成两部分
        vector<ll> areas = {area1, sub_area, area2 - sub_area};
        sort(areas.begin(), areas.end());
        ll current_diff = areas[2] - areas[0];     // 计算当前不平衡值
        min_diff = min(min_diff, current_diff);

        // [FIX] 提前终止条件：如果当前不平衡值已大于等于最优解，则无需继续
        if (current_diff >= min_diff) break;
    }

    // [FIX] 数学优化：对于特殊情况，直接计算可能的最小不平衡值
    // 如果总面积不能被3整除，则尝试计算最接近的三个面积分配方案
    // 例如：area1 = floor(total_area / 3), area2 = ceil(total_area / 3), area3 = total_area - area1 - area2
    ll target = total_area / 3;
    for (ll k = -1; k <= 1; ++k) {  // 枚举可能的偏差
        ll area1 = target + k;
        if (area1 <= 0 || area1 > total_area) continue;  // 面积必须合法
        ll area2 = (total_area - area1) / 2;
        ll area3 = total_area - area1 - area2;
        if (area2 <= 0 || area3 <= 0) continue;  // 面积必须合法
        vector<ll> areas = {area1, area2, area3};
        sort(areas.begin(), areas.end());
        ll current_diff = areas[2] - areas[0];
        min_diff = min(min_diff, current_diff);
    }

    cout << min_diff << "\n";  // 输出最小不平衡值
}