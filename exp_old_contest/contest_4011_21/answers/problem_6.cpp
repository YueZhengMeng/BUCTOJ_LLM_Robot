/* 文件头注释：子集排名计算，利用二进制表示和数学公式优化 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> subset(k);
    for (int i = 0; i < k; ++i) {
        cin >> subset[i];
    }

    int rank = 0;
    int prev = 0;
    for (int i = 0; i < k; ++i) {
        int current = subset[i];
        // 计算在prev和current之间的所有可能的子集数量
        rank += (1 << (current - prev - 1));
        prev = current;
    }

    // 最后加上所有比当前子集小的子集数量
    rank += (1 << (n - prev)) - 1;

    cout << rank << endl;
    return 0;
}