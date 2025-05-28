/* 文件头注释：模拟公交车上下车过程，记录最大人数 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    while (cin >> n >> m) {  // 处理多组样例
        int max_people = m;  // 初始化最大人数为初始人数
        int current_people = m;  // 当前车上人数
        for (int i = 0; i < n; ++i) {
            int pi, qi;
            cin >> pi >> qi;
            current_people += pi - qi;  // 更新当前人数
            if (current_people < 0) {  // 确保人数不为负
                current_people = 0;
            }
            if (current_people > max_people) {  // 更新最大人数
                max_people = current_people;
            }
        }
        cout << max_people << endl;  // 输出结果
    }
    return 0;
}