/* 文件头注释：使用二分搜索和贪心算法确定最少厨师数量 */
#include <bits/stdc++.h>
using namespace std;

// 检查是否可以在给定时间内完成所有任务
bool canComplete(int N, int K, const vector<int>& a, int chefs) {
    // [FIX] 检查是否有任何一道菜的时间超过K
    for (int i = 0; i < N; ++i) {
        if (a[i] > K) {
            return false;
        }
    }

    int totalTime = 0;
    for (int i = 0; i < N; ++i) {
        if (totalTime + a[i] > K) {
            chefs--;
            totalTime = 0;
            if (chefs < 0) return false;
        }
        totalTime += a[i];
    }
    return true;
}

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }

    // 计算总时间，如果总时间超过K，直接输出-1
    long long total = accumulate(a.begin(), a.end(), 0LL);
    if (total > K) {
        cout << -1 << endl;
        return 0;
    }

    // 二分搜索确定最少厨师数量
    int left = 1, right = N;
    while (left < right) {
        int mid = (left + right) / 2;
        if (canComplete(N, K, a, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    cout << left << endl;
    return 0;
}