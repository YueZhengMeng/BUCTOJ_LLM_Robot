/* 文件头注释：快速排序算法实现 */
#include <bits/stdc++.h>
using namespace std;

// 快速排序的分区函数
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // 选择最后一个元素作为枢轴
    int i = low - 1; // i是小于枢轴的元素的分界点

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]); // 将枢轴放到正确的位置
    return i + 1;
}

// 快速排序的递归函数
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // 获取分区点
        quickSort(arr, low, pi - 1); // 对左半部分排序
        quickSort(arr, pi + 1, high); // 对右半部分排序
    }
}

int main() {
    int t;
    cin >> t; // 输入样例组数

    while (t--) {
        int n;
        cin >> n; // 输入数列中元素的个数
        vector<int> arr(n);

        for (int i = 0; i < n; ++i) {
            cin >> arr[i]; // 依次输入数列中的元素
        }

        quickSort(arr, 0, n - 1); // 调用快速排序

        for (int i = 0; i < n; ++i) {
            cout << arr[i] << " "; // 输出排序后的数列
        }
        cout << endl;
    }

    return 0;
}