/* 文件头注释：利用毕达哥拉斯三元组构造满足条件的点 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    // 使用毕达哥拉斯三元组 (3, 4, 5) 来构造点
    // 第一个点固定在 (0, 0)
    cout << "0 0" << endl;
    
    // 后续点按照 (3k, 0) 和 (3k, 4k) 的方式构造
    for (int i = 1; i < n; ++i) {
        if (i % 2 == 1) {
            cout << 3 * (i / 2 + 1) << " 0" << endl;
        } else {
            cout << 3 * (i / 2) << " " << 4 * (i / 2) << endl;
        }
    }
    
    return 0;
}