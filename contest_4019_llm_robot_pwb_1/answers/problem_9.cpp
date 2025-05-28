/* 文件头注释：枚举法找出所有水仙花数 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    // 遍历所有三位数
    for (int num = 100; num <= 999; ++num) {
        int originalNum = num;
        int sum = 0;
        
        // 计算各位数字的立方和
        while (originalNum != 0) {
            int digit = originalNum % 10;
            sum += digit * digit * digit;
            originalNum /= 10;
        }
        
        // 如果立方和等于原数，则输出
        if (sum == num) {
            cout << num << endl;
        }
    }
    return 0;
}