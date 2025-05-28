/* 文件头注释：四位数数字间插入空格 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int num;
    cin >> num;  // 读取输入的四位数

    // 提取每一位数字
    int thousands = num / 1000;
    int hundreds = (num / 100) % 10;
    int tens = (num / 10) % 10;
    int units = num % 10;

    // 输出结果，每两个数字间插入空格
    cout << thousands << " " << hundreds << " " << tens << " " << units << endl;

    return 0;
}