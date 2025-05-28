/* 文件头注释：使用Zeller公式计算特定年份中既是星期五又是13号的天数 */
#include <bits/stdc++.h>
using namespace std;

// 判断是否为闰年
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 使用Zeller公式计算某一天是星期几
int zeller(int year, int month, int day) {
    if (month < 3) {
        month += 12;
        year -= 1;
    }
    int c = year / 100;
    int y = year % 100;
    int m = month;
    int d = day;
    int w = (y + y / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10 + d - 1) % 7;
    if (w < 0) w += 7;
    return w;
}

int main() {
    int year;
    cin >> year;
    int count = 0;
    for (int month = 1; month <= 12; ++month) {
        if (zeller(year, month, 13) == 5) {
            count++;
        }
    }
    cout << count << endl;
    return 0;
}