/* 文件头注释：二分搜索算法，用于在电缆长度中寻找最大切割长度 */
#include <bits/stdc++.h>
using namespace std;

// 判断是否能够切割出至少k条长度为mid的电缆
bool canCut(const vector<double>& cables, int k, double mid) {
    int count = 0;
    for (double length : cables) {
        count += static_cast<int>(floor(length / mid));
        if (count >= k) return true;
    }
    return false;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<double> cables(n);
    for (int i = 0; i < n; ++i) {
        cin >> cables[i];
    }

    double left = 0.0, right = *max_element(cables.begin(), cables.end());
    double result = 0.0;

    // 二分搜索，精度设置为1e-5
    while (right - left > 1e-5) {
        double mid = (left + right) / 2;
        if (canCut(cables, k, mid)) {
            result = mid;
            left = mid;
        } else {
            right = mid;
        }
    }

    // 输出结果，保留两位小数
    cout << fixed << setprecision(2) << result << endl;

    return 0;
}