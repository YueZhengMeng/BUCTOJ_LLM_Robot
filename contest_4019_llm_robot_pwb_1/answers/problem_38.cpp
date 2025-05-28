/* 文件头注释：说明核心算法名称和关键技术 */
#include <bits/stdc++.h>
using namespace std;

// 输入10个数
void inputNumbers(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
}

// 进行处理：找到最小值和最大值的位置，并进行交换
void processNumbers(int arr[], int n) {
    int minIndex = 0, maxIndex = 0;
    
    // 找到最小值和最大值的位置
    for (int i = 1; i < n; ++i) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
        if (arr[i] > arr[maxIndex]) {
            maxIndex = i;
        }
    }
    
    // 交换最小值和第一个数
    swap(arr[0], arr[minIndex]);
    
    // 如果最大值原本在第一个位置，由于已经交换过，需要更新maxIndex
    if (maxIndex == 0) {
        maxIndex = minIndex;
    }
    
    // 交换最大值和最后一个数
    swap(arr[n - 1], arr[maxIndex]);
}

// 输出10个数
void outputNumbers(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    const int n = 10;
    int arr[n];
    
    // 输入10个数
    inputNumbers(arr, n);
    
    // 进行处理
    processNumbers(arr, n);
    
    // 输出10个数
    outputNumbers(arr, n);
    
    return 0;
}