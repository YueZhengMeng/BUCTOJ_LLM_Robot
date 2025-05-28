/* 
算法名称：Greedy Allocation
关键技巧：通过改进的贪心策略将苹果分配到尽可能多的天数上，避免连续两天不吃苹果。
主要修改标记：[FIX] 说明修改原因
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a;
    cin >> n >> a;

    // 边界条件处理 [FIX]: 增强边界条件处理
    if (n == 0) {
        cout << 0 << "\n"; // 如果没有天数，医生访问次数为0
        return 0;
    }
    if (a == 0) {
        cout << max(0, n - 1) << "\n"; // 如果没有苹果，则医生访问次数为n-1
        return 0;
    }
    if (a >= n) {
        cout << 0 << "\n"; // 如果苹果数量大于等于天数，医生访问次数为0
        return 0;
    }

    // 改进的贪心分配苹果 [FIX]: 优先分配到间隔为2的天数上
    vector<bool> eaten(n, false); // 记录每天是否吃了苹果
    int doctorVisits = 0; // 医生访问次数

    // 尽量将苹果分配到间隔为2的天数上
    for (int i = 0; i < n && a > 0; ++i) {
        if (!eaten[i]) { // 如果当天没有吃苹果
            eaten[i] = true; // 分配一个苹果
            a--; // 减少剩余苹果数量
        }
        if (a > 0 && i + 2 < n && !eaten[i + 2]) { // 如果还能分配且间隔为2的天数没吃苹果
            eaten[i + 2] = true; // 分配一个苹果
            a--;
        }
    }

    // 检查连续两天未吃苹果的情况 [FIX]: 优化连续两天未吃苹果的检查逻辑
    for (int i = 1; i < n; ++i) {
        if (!eaten[i] && !eaten[i - 1]) { // 如果当前天和前一天都没吃苹果
            doctorVisits++; // 触发医生访问
        }
    }

    // DEBUG: 输出中间状态
    // for (int i = 0; i < n; ++i) {
    //     cout << "Day " << i + 1 << ": " << (eaten[i] ? "Eaten" : "Not Eaten") << "\n";
    // }

    cout << doctorVisits << "\n";
    return 0;
}