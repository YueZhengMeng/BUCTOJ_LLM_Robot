/* 文件头注释：说明核心算法名称和关键技术 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    const int N = 10; // 定义常量N为10
    int nums[N]; // 存储输入的10个整数
    for (int i = 0; i < N; ++i) {
        cin >> nums[i]; // 读取输入
    }

    int max_val = nums[0], min_val = nums[0]; // 初始化最大值和最小值为第一个元素
    for (int i = 1; i < N; ++i) {
        if (nums[i] > max_val) {
            max_val = nums[i]; // 更新最大值
        }
        if (nums[i] < min_val) {
            min_val = nums[i]; // 更新最小值
        }
    }

    // 输出最大值和最小值
    cout << max_val << endl;
    cout << min_val << endl;

    // 按照输入顺序输出10个数
    for (int i = 0; i < N; ++i) {
        if (i > 0) {
            cout << " ";
        }
        cout << nums[i];
    }
    cout << endl;

    return 0;
}