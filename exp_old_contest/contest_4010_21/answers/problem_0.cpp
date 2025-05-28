/* 文件头注释：人元纪年与公元纪年转换 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int x; // 输入的人元年份
    cin >> x;
    int y = x - 10000; // 转换为公元年份

    if (y <= 0) {
        // 如果转换后的年份小于等于0，表示公元前
        // [FIX] 修改为 -(y - 1) 以正确处理人元10000年（对应公元前1年）
        cout << -(y - 1) << " BC" << endl;
    } else {
        // 否则表示公元后
        cout << "AD " << y << endl;
    }

    return 0;
}