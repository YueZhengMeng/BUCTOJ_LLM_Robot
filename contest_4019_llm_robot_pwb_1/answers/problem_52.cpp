/* 文件头注释：逆序输出数组元素 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    const int SIZE = 20; // 定义数组大小
    int arr[SIZE]; // 存储输入的20个整数

    // 输入20个整数
    for (int i = 0; i < SIZE; ++i) {
        cin >> arr[i];
    }

    // 逆序输出数组元素
    for (int i = SIZE - 1; i >= 0; --i) {
        cout << arr[i];
        if (i > 0) {
            cout << " "; // 每个整数之间用空格分隔，最后一个后面无空格
        }
    }
    cout << endl; // 输出结束后换行

    return 0;
}