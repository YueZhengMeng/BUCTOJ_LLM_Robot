/* 文件头注释：使用队列模拟约瑟夫问题 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n; // 输入初始人数

    if (n == 1) {
        cout << 1 << endl; // 边界情况，只有一个人时直接输出1
        return 0;
    }

    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        q.push(i); // 初始化队列，按顺序排号
    }

    int count = 0;
    while (q.size() > 1) {
        int current = q.front();
        q.pop();
        count++;
        if (count % 3 != 0) {
            q.push(current); // 如果报数不是3，重新加入队列
        }
    }

    cout << q.front() << endl; // 输出最后剩下的人的编号
    return 0;
}