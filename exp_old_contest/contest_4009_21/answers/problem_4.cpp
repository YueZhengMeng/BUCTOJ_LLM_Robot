/* 文件头注释：调整策略，每次选择掌握程度最高的英雄进行特训 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int Y, M, L;
    cin >> Y >> M >> L;
    string result;
    int steps = 0;
    while (steps < 1000) {
        // 检查是否已经有两个英雄的掌握程度为0
        int zeroCount = 0;
        if (Y == 0) zeroCount++;
        if (M == 0) zeroCount++;
        if (L == 0) zeroCount++;
        if (zeroCount >= 2) {
            cout << result << endl;
            return 0;
        }
        // 选择掌握程度最高的英雄进行特训
        if (Y >= M && Y >= L) {
            Y++;
            M = max(M - 1, 0);
            L = max(L - 1, 0);
            result += 'Y';
        } else if (M >= Y && M >= L) {
            M++;
            Y = max(Y - 1, 0);
            L = max(L - 1, 0);
            result += 'M';
        } else {
            L++;
            Y = max(Y - 1, 0);
            M = max(M - 1, 0);
            result += 'L';
        }
        steps++;
    }
    // 如果超过1000次操作仍未达到目标，输出-1
    cout << "-1" << endl;
    return 0;
}