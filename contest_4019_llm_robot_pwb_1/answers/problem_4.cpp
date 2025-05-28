/* 文件头注释：使用条件判断语句找出三个整数中的最大值 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c;
    // 从标准输入读取三个整数
    cin >> a >> b >> c;
    
    // 使用条件判断找出最大值
    int max_num = a;
    if (b > max_num) {
        max_num = b;
    }
    if (c > max_num) {
        max_num = c;
    }
    
    // 输出最大值
    cout << max_num << endl;
    
    return 0;
}