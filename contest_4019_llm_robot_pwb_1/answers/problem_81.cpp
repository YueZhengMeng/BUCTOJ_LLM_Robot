/* 文件头注释：二分查找与递推公式结合，确定最右侧灯的最低高度 */
#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9; // 用于浮点数比较的精度

// 检查给定B是否满足所有灯高度非负
bool check(int N, double A, double B) {
    double prev = A, curr = 0;
    for (int i = 2; i <= N; ++i) {
        curr = 2 * (prev + 1) - (i == N ? B : 0);
        if (curr < 0) return false;
        prev = curr;
    }
    return true;
}

int main() {
    int N;
    double A;
    cin >> N >> A;

    double left = 0, right = 1e6; // B的可能范围
    while (right - left > EPS) {
        double mid = (left + right) / 2;
        if (check(N, A, mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }

    cout << fixed << setprecision(2) << left << endl;
    return 0;
}