/* 文件头注释：使用宏定义实现变量交换 */
#include <bits/stdc++.h>
using namespace std;

// 定义带参的宏，用于交换两个变量的值
#define SWAP(a, b) { int temp = a; a = b; b = temp; }

int main() {
    int num1, num2;
    // 输入两个数
    cin >> num1 >> num2;
    // 使用宏交换两个数的值
    SWAP(num1, num2);
    // 输出交换后的结果
    cout << num1 << " " << num2 << endl;
    return 0;
}