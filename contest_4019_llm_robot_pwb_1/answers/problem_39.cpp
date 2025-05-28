/* 文件头注释：使用反转法实现数组循环移动 */
#include <bits/stdc++.h>
using namespace std;

// 反转数组的指定范围
void reverseArray(vector<int>& nums, int start, int end) {
    while (start < end) {
        swap(nums[start], nums[end]);
        start++;
        end--;
    }
}

// 实现数组循环移动
void rotateArray(vector<int>& nums, int m) {
    int n = nums.size();
    m = m % n; // 处理m大于n的情况
    reverseArray(nums, 0, n - 1); // 反转整个数组
    reverseArray(nums, 0, m - 1); // 反转前m个元素
    reverseArray(nums, m, n - 1); // 反转剩下的n-m个元素
}

int main() {
    int n, m;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    cin >> m;
    
    rotateArray(nums, m);
    
    for (int i = 0; i < n; ++i) {
        cout << nums[i] << " ";
    }
    cout << endl;
    
    return 0;
}