/* 文件头注释：模拟小T征服女生的过程 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int T, n;
    cin >> T >> n;  // 读取小T的魅力值和其他女生的人数
    for (int i = 0; i < n; ++i) {
        int M;
        cin >> M;  // 读取当前女生的魅力值
        if (T > M) {
            T += M;  // 如果小T的魅力值更高，则征服并累加魅力值
        } else if (T < M) {
            cout << "Oh no, so charming she is." << endl;  // 如果小T的魅力值更低，则输出失败
            return 0;
        } else {
            cout << "Oh no, so charming she is." << endl;  // 如果魅力值相同，则输出失败
            return 0;
        }
    }
    cout << "I'm the queen today!" << endl;  // 如果成功征服所有女生，则输出成功
    return 0;
}