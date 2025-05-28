/* 文件头注释：使用std::sort对数组进行排序，然后直接取中位数 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;  // 读取整数n
    vector<int> nums(n);  // 创建一个大小为n的vector来存储数字
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];  // 读取每个数字
    }
    sort(nums.begin(), nums.end());  // 对数组进行排序
    cout << nums[n / 2] << endl;  // 输出中位数
    return 0;
}