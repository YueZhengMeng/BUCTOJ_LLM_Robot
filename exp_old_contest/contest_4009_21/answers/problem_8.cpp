/* 文件头注释：使用树状数组统计区间内比某个数大的数的个数 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 10;

int N;
int a[MAXN * 2];
int firstPos[MAXN];
int secondPos[MAXN];
int bit[MAXN * 2];

// 树状数组的更新操作
void update(int idx, int val) {
    while (idx <= 2 * N) {
        bit[idx] += val;
        idx += idx & -idx;
    }
}

// 树状数组的查询操作
int query(int idx) {
    int res = 0;
    while (idx > 0) {
        res += bit[idx];
        idx -= idx & -idx;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 1; i <= 2 * N; ++i) {
        cin >> a[i];
    }

    memset(firstPos, 0, sizeof(firstPos));
    memset(secondPos, 0, sizeof(secondPos));
    memset(bit, 0, sizeof(bit));

    // 记录每个数字的第一次和第二次出现位置
    for (int i = 1; i <= 2 * N; ++i) {
        if (firstPos[a[i]] == 0) {
            firstPos[a[i]] = i;
        } else {
            secondPos[a[i]] = i;
        }
    }

    long long total = 0;

    // 按照数字从大到小的顺序处理
    for (int num = N; num >= 1; --num) {
        int cnt = query(secondPos[num]) - query(firstPos[num]);
        total += cnt;
        // 标记当前数字的两个位置
        update(firstPos[num], 1);
        update(secondPos[num], 1);
    }

    cout << total << endl;

    return 0;
}