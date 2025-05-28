/* 文件头注释：计算给定日期在当年中的第几天，考虑闰年问题 */
#include <bits/stdc++.h>
using namespace std;

// 判断是否为闰年
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 计算给定日期是当年的第几天
int dayOfYear(int year, int month, int day) {
    // 每个月的天数，注意2月的天数在闰年和非闰年时不同
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year)) {
        daysInMonth[1] = 29; // 闰年2月有29天
    }
    
    int dayOfYear = 0;
    for (int i = 0; i < month - 1; ++i) {
        dayOfYear += daysInMonth[i]; // 累加前几个月的天数
    }
    dayOfYear += day; // 加上当前月的天数
    return dayOfYear;
}

int main() {
    int year, month, day;
    cin >> year >> month >> day;
    cout << dayOfYear(year, month, day) << endl;
    return 0;
}