/* 文件头注释：说明核心算法名称和关键技术 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    // 计算所有石子的总数
    long long total = accumulate(a.begin(), a.end(), 0LL);
    
    // 计算最大堆的石子数
    long long max_pile = *max_element(a.begin(), a.end());
    
    // 如果最大堆的石子数超过总数的一半，则操作次数为总数减去最大堆的石子数
    // 否则，操作次数为总数除以2
    long long result = min(total - max_pile, total / 2);
    
    cout << result << endl;
    return 0;
}