/* 文件头注释：贪心算法，按就餐时间从大到小排序 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> guests(n);
    for (int i = 0; i < n; ++i) {
        cin >> guests[i].first >> guests[i].second;
    }
    
    // 按就餐时间从大到小排序
    sort(guests.begin(), guests.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    });
    
    int total_time = 0;
    int current_time = 0;
    for (const auto& guest : guests) {
        current_time += guest.first;
        total_time = max(total_time, current_time + guest.second);
    }
    
    cout << total_time << endl;
    return 0;
}