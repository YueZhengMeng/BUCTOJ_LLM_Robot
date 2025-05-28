/* 文件头注释：核心算法为数学推导，关键技术为三角函数的应用 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int a, b, c;
        cin >> a >> b >> c;
        // 计算 X 和 Y 的平方
        double X_squared = (double)a / b;
        double Y_squared = 1.0 / c;
        // 判断是否可以通过一次操作将 X 转换为 Y
        // 由于操作次数限制为 2*b 次，且 X 和 Y 都是平方根形式，我们可以通过数学推导来判断
        // 如果 X_squared == Y_squared，则直接输出 YES
        if (X_squared == Y_squared) {
            cout << "YES" << endl;
            continue;
        }
        // 否则，判断是否可以通过一次操作将 X 转换为 Y
        // 由于操作次数限制为 2*b 次，且 X 和 Y 都是平方根形式，我们可以通过数学推导来判断
        // 如果 X_squared == 1 - Y_squared，则可以通过一次 arccos 或 arcsin 操作实现
        if (X_squared == 1 - Y_squared) {
            cout << "YES" << endl;
            continue;
        }
        // 否则，输出 NO
        cout << "NO" << endl;
    }
    return 0;
}