/* 文件头注释：归并排序算法实现 */
#include <bits/stdc++.h>
using namespace std;

// 合并两个有序数组
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    // 合并两个有序数组
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // 将剩余元素复制到临时数组
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // 将临时数组中的元素复制回原数组
    for (int p = 0; p < k; ++p) {
        arr[left + p] = temp[p];
    }
}

// 归并排序递归函数
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);      // 对左半部分排序
        mergeSort(arr, mid + 1, right); // 对右半部分排序
        merge(arr, left, mid, right);   // 合并两个有序部分
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }

        // 调用归并排序
        mergeSort(arr, 0, n - 1);

        // 输出排序结果
        for (int i = 0; i < n; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    return 0;
}