/* 文件头注释：使用代数方法求解二元一次方程组 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int A, B;
    cin >> A >> B;  // 读取输入的A和B

    // 通过代数方法求解x和y
    int x = (A + B) / 2;
    int y = (A - B) / 2;

    // 输出结果
    cout << x << " " << y << endl;

    return 0;
}