/* 文件头注释：使用选择排序算法对10个整数进行排序 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    const int N = 10;
    int arr[N];
    
    // 输入10个整数
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }
    
    // 选择排序
    for (int i = 0; i < N - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < N; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // 交换arr[i]和arr[minIndex]
        swap(arr[i], arr[minIndex]);
    }
    
    // 输出排序后的结果
    for (int i = 0; i < N; ++i) {
        cout << arr[i] << endl;
    }
    
    return 0;
}