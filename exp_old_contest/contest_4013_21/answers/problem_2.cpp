/* 文件头注释：核心算法为数学公式计算最小和最大路径和 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long n, k;
        cin >> n >> k;
        
        // 计算最小路径和：从起点到终点只向右或只向上
        long long min_sum = (1 + n) * n / 2 + (n + n * n) * n / 2 - n;
        
        // 计算最大路径和：从起点到终点尽可能多地向右和向上
        long long max_sum = (1 + n) * n / 2 + (n + n * n) * n / 2 - n;
        
        // 判断k是否在最小和最大路径和之间
        if (k >= min_sum && k <= max_sum) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}