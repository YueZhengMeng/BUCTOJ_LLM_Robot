/* 文件头注释：使用标准库的sort和lower_bound进行排序和查找 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t; // 读取样例组数
    while (t--) {
        int n;
        cin >> n; // 读取数列中元素的个数
        vector<int> nums(n);
        for (int i = 0; i < n; ++i) {
            cin >> nums[i]; // 依次读取数列中的元素
        }
        int p;
        cin >> p; // 读取要查找的元素

        // 对数列进行升序排序
        sort(nums.begin(), nums.end());

        // 输出排序后的数列
        for (int i = 0; i < n; ++i) {
            cout << nums[i] << (i == n - 1 ? "\n" : " ");
        }

        // 使用lower_bound进行二分查找
        auto it = lower_bound(nums.begin(), nums.end(), p);
        if (it != nums.end() && *it == p) {
            // 如果找到，输出位置（从1开始计数）
            cout << (it - nums.begin() + 1) << endl;
        } else {
            // 如果未找到，输出-1
            cout << -1 << endl;
        }
    }
    return 0;
}