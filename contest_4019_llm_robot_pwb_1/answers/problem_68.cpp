/* 文件头注释：使用中国剩余定理解决同余问题 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    // 从最大的模数开始，逐步满足所有条件
    int step = 7; // 每次跨7阶，最后正好1阶不剩
    while (true) {
        if (step % 2 == 1 && step % 3 == 2 && step % 5 == 4 && step % 6 == 5) {
            cout << step << endl;
            break;
        }
        step += 7; // 每次增加7，确保满足最后一个条件
    }
    return 0;
}