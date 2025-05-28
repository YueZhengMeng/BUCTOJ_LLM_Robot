/* 文件头注释：交换最小数，通过遍历找到最小元素并交换 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;  // 输入数组的大小
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];  // 输入数组元素
    }

    int minIndex = 0;  // 初始化最小值的索引为0
    for (int i = 1; i < n; ++i) {
        if (nums[i] < nums[minIndex]) {
            minIndex = i;  // 更新最小值的索引
        }
    }

    // 交换最小值和第一个元素
    swap(nums[0], nums[minIndex]);

    // 输出交换后的数组
    for (int i = 0; i < n; ++i) {
        cout << nums[i] << " ";
    }
    cout << endl;

    return 0;
}