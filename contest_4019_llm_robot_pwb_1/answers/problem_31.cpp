/* 文件头注释：使用宏计算三角形面积 */
#include <bits/stdc++.h>
using namespace std;

// 定义宏来计算S
#define S(a, b, c) ((a + b + c) / 2.0)

// 定义宏来计算面积
#define AREA(a, b, c) (sqrt(S(a, b, c) * (S(a, b, c) - a) * (S(a, b, c) - b) * (S(a, b, c) - c)))

int main() {
    double a, b, c;
    // 输入三角形的三条边
    cin >> a >> b >> c;
    
    // 计算并输出面积，保留3位小数
    cout << fixed << setprecision(3) << AREA(a, b, c) << endl;
    
    return 0;
}