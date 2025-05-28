/* 文件头注释：使用Johnson规则解决两台机器的流水线调度问题 */
#include <bits/stdc++.h>
using namespace std;

struct Job {
    int id; // 零件编号
    int time1; // 机器1的加工时间
    int time2; // 机器2的加工时间
};

// 比较函数，用于Johnson规则排序
bool compare(Job a, Job b) {
    return min(a.time1, b.time2) < min(b.time1, a.time2);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<Job> jobs(n);
        for (int i = 0; i < n; ++i) {
            jobs[i].id = i + 1;
            cin >> jobs[i].time1 >> jobs[i].time2;
        }
        
        // 按照Johnson规则排序
        sort(jobs.begin(), jobs.end(), compare);
        
        // 计算总加工时间
        int time1 = 0, time2 = 0;
        for (int i = 0; i < n; ++i) {
            time1 += jobs[i].time1;
            time2 = max(time2, time1) + jobs[i].time2;
        }
        
        cout << time2 << endl;
    }
    return 0;
}