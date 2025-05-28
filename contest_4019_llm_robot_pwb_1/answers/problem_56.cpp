/* 文件头注释：核心算法为贪心算法，关键技术为统计糖果数量并判断是否满足条件 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> candyCount(1000001, 0); // 假设糖果编号最大为1000000
        int maxCount = 0;
        for (int i = 0; i < N; ++i) {
            int candy;
            cin >> candy;
            candyCount[candy]++;
            if (candyCount[candy] > maxCount) {
                maxCount = candyCount[candy];
            }
        }
        // 如果某种糖果的数量超过总天数的一半，则无法满足条件
        if (maxCount > (N + 1) / 2) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
        }
    }
    return 0;
}