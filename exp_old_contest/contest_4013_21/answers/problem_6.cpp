/* 文件头注释：使用贪心算法和双指针技术最大化数组中元素$a_i$大于$b_i$的次数 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b[i] = a[i];
    }
    
    // 对数组a和b进行排序
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    
    int count = 0;
    int i = 0, j = 0;
    
    // 使用双指针技术匹配a[i]和b[j]
    while (i < n && j < n) {
        if (a[i] > b[j]) {
            count++;
            i++;
            j++;
        } else {
            i++;
        }
    }
    
    cout << count << endl;
    return 0;
}