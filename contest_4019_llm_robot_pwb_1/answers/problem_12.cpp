/* 文件头注释：模拟自由落体运动，计算第N次落地时的反弹高度和总经过距离 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    double M; // 初始高度
    int N;    // 落地次数
    cin >> M >> N;

    double height = M; // 当前高度
    double distance = 0; // 总经过距离

    for (int i = 1; i <= N; ++i) {
        distance += height; // 下落距离
        height /= 2;        // 反弹高度
        if (i < N) {
            distance += height; // 上升距离（除了最后一次）
        }
    }

    // 输出结果，保留两位小数
    cout << fixed << setprecision(2) << height << " " << distance << endl;

    return 0;
}