/* 魔力转换：逐位判断奇偶生成符号 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    string s = to_string(n), res;
    for (char c : s) {
        int digit = c - '0';
        res += (digit % 2 ? '#' : '*');
    }
    cout << res << '\n';  // [FIX] 添加换行符以满足OJ格式要求
    return 0;
}