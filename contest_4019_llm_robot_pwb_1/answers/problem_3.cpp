/* 文件头注释：华氏温度转摄氏温度，使用标准公式计算并格式化输出 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    double fahrenheit;  // 输入的华氏温度
    cin >> fahrenheit;  // 读取输入

    // 根据公式计算摄氏温度
    double celsius = 5 * (fahrenheit - 32) / 9;

    // 格式化输出，保留两位小数
    cout << fixed << setprecision(2) << "c=" << celsius << endl;

    return 0;
}