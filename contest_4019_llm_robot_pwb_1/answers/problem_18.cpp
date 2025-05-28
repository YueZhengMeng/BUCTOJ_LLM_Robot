/* 文件头注释：使用二分查找找到插入位置，然后插入新元素 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    // 读取原始数组
    vector<int> arr(9);
    for (int i = 0; i < 9; ++i) {
        cin >> arr[i];
    }
    
    // 读取要插入的数字
    int num;
    cin >> num;
    
    // 使用二分查找找到插入位置
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < num) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    // 在找到的位置插入新元素
    arr.insert(arr.begin() + left, num);
    
    // 输出排序后的数组
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << endl;
    }
    
    return 0;
}