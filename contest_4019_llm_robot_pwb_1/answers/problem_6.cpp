/* 文件头注释：使用switch-case结构计算企业奖金提成 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int profit; // 当月利润
    cin >> profit;
    int bonus = 0; // 应发奖金总数

    // 根据利润的不同区间计算奖金
    switch (profit / 100000) {
        case 0: // 利润 <= 100000
            bonus = profit * 0.10;
            break;
        case 1: // 100000 < 利润 <= 200000
            bonus = 100000 * 0.10 + (profit - 100000) * 0.075;
            break;
        case 2: // 200000 < 利润 <= 400000
        case 3:
            bonus = 100000 * 0.10 + 100000 * 0.075 + (profit - 200000) * 0.05;
            break;
        case 4: // 400000 < 利润 <= 600000
        case 5:
            bonus = 100000 * 0.10 + 100000 * 0.075 + 200000 * 0.05 + (profit - 400000) * 0.03;
            break;
        case 6: // 600000 < 利润 <= 1000000
        case 7:
        case 8:
        case 9:
            bonus = 100000 * 0.10 + 100000 * 0.075 + 200000 * 0.05 + 200000 * 0.03 + (profit - 600000) * 0.015;
            break;
        default: // 利润 > 1000000
            bonus = 100000 * 0.10 + 100000 * 0.075 + 200000 * 0.05 + 200000 * 0.03 + 400000 * 0.015 + (profit - 1000000) * 0.01;
            break;
    }

    cout << bonus << endl;
    return 0;
}