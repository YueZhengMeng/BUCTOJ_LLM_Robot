/* 文件头注释：判断水仙花数 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int num;
    cin >> num;
    
    // 检查是否为三位数
    if (num < 100 || num > 999) {
        cout << "NO" << endl;
        return 0;
    }
    
    // 提取各位数字
    int hundreds = num / 100;
    int tens = (num / 10) % 10;
    int units = num % 10;
    
    // 计算立方和
    int sum_of_cubes = hundreds * hundreds * hundreds + tens * tens * tens + units * units * units;
    
    // 判断是否为水仙花数
    if (sum_of_cubes == num) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    
    return 0;
}