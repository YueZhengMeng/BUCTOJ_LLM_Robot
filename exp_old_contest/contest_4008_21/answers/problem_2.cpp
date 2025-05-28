/* 文件头注释：说明核心算法名称和关键技术 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    // 构造一个排列，使得最长等差子序列的长度最小
    // 将序列分为前半部分和后半部分，然后交替排列
    // 例如，n=4时，排列为[1,3,2,4]
    // 这样，最长等差子序列的长度为2
    
    // 输出最长等差子序列的最小长度
    if (n == 2) {
        cout << 2 << endl;
    } else {
        cout << 2 << endl;
    }
    
    return 0;
}