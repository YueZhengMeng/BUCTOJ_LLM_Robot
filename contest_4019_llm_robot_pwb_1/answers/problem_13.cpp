/* 文件头注释：猴子吃桃问题，使用逆向递推算法 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;  // 输入天数N
    int peaches = 1;  // 第N天剩下的桃子数
    for (int i = N; i > 1; --i) {
        peaches = (peaches + 1) * 2;  // 逆向推导前一天的桃子数
    }
    cout << peaches << endl;  // 输出第1天的桃子总数
    return 0;
}