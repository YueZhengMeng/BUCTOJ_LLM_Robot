/* 文件头注释：选择困难问题，贪心算法，计算当前位置到最近出口的最短时间 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t; // 输入当前位置
    int min_time = INT_MAX; // 初始化最小时间为最大值

    // 遍历所有出口，计算到当前位置的距离
    for (int exit_pos = 0; exit_pos <= 100; exit_pos += 5) {
        int distance = abs(t - exit_pos); // 计算距离
        if (distance < min_time) {
            min_time = distance; // 更新最小时间
        }
    }

    cout << min_time << endl; // 输出最小时间
    return 0;
}