/* 文件头注释：滑动窗口算法，用于计算最大COMBO数 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;

    int left = 0, right = 0; // 滑动窗口的左右指针
    int max_combo = 0; // 最大COMBO数
    int zero_count = 0; // 当前窗口内0的个数

    while (right < n) {
        if (s[right] == '0') {
            zero_count++;
        }
        // 当窗口内0的个数超过m时，移动左指针
        while (zero_count > m) {
            if (s[left] == '0') {
                zero_count--;
            }
            left++;
        }
        // 更新最大COMBO数
        max_combo = max(max_combo, right - left + 1);
        right++;
    }

    cout << max_combo << endl;
    return 0;
}