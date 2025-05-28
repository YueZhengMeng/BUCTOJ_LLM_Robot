/* 文件头注释：找出缺失的排列，使用异或运算逐个字符比较 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    // 用于存储每个位置上字符的异或结果
    vector<int> missingPerm(n, 0);
    
    // 读取输入的排列
    for (int i = 0; i < factorial(n) - 1; ++i) {
        string perm;
        cin >> perm;
        for (int j = 0; j < n; ++j) {
            missingPerm[j] ^= (perm[j] - '0');
        }
    }
    
    // 构造缺失的排列
    string result;
    for (int j = 0; j < n; ++j) {
        result += to_string(missingPerm[j]);
    }
    
    cout << result << endl;
    
    return 0;
}

// 辅助函数：计算n的阶乘
int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}