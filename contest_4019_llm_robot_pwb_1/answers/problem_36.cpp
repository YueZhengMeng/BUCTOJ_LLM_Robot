/* 文件头注释：使用简单的比较和交换操作对三个整数进行排序 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;

    // 通过比较和交换确保a <= b <= c
    if (a > b) swap(a, b);
    if (a > c) swap(a, c);
    if (b > c) swap(b, c);

    // 输出排序后的结果
    cout << a << " " << b << " " << c << " " << endl;

    return 0;
}