/* 文件头注释：判断闰年的宏定义 */
#include <bits/stdc++.h>
using namespace std;

// 定义宏LEAP_YEAR，判断年份y是否为闰年
#define LEAP_YEAR(y) (((y) % 4 == 0 && (y) % 100 != 0) || (y) % 400 == 0 ? "L" : "N")

int main() {
    int year;
    cin >> year;  // 输入年份
    cout << LEAP_YEAR(year) << endl;  // 输出判断结果
    return 0;
}