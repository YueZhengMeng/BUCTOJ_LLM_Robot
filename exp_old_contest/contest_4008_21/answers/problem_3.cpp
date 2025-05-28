/* 文件头注释：魔力值到魔法阵图案的转换 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;  // 读取输入的魔力值
    string result = "";  // 初始化结果字符串

    // 处理特殊情况，当n为0时
    if (n == 0) {
        cout << "*" << endl;
        return 0;
    }

    // 遍历每一位数字
    while (n > 0) {
        int digit = n % 10;  // 获取当前位的数字
        if (digit % 2 == 0) {
            result = '*' + result;  // 偶数转换为*
        } else {
            result = '#' + result;  // 奇数转换为#
        }
        n /= 10;  // 去掉已处理的最后一位
    }

    cout << result << endl;  // 输出最终结果
    return 0;
}