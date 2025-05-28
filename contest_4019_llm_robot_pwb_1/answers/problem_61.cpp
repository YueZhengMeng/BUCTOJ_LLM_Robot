/* 文件头注释：统计校友编号出现次数，找出出现次数最多的编号 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    unordered_map<int, int> countMap; // 用于统计每个编号的出现次数
    int num;
    while (cin >> num && num >= 0) {
        countMap[num]++; // 统计编号出现次数
    }

    int maxCount = 0;
    for (const auto& pair : countMap) {
        if (pair.second > maxCount) {
            maxCount = pair.second; // 找出最大出现次数
        }
    }

    vector<int> winners;
    for (const auto& pair : countMap) {
        if (pair.second == maxCount) {
            winners.push_back(pair.first); // 收集出现次数最多的编号
        }
    }

    sort(winners.begin(), winners.end()); // 按编号从小到大排序

    for (size_t i = 0; i < winners.size(); ++i) {
        if (i > 0) cout << " ";
        cout << winners[i]; // 输出结果
    }
    cout << endl;

    return 0;
}