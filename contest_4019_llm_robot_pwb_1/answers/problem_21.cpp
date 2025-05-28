/* 文件头注释：二次方程求根，根据判别式分类处理 */
#include <bits/stdc++.h>
using namespace std;

// 当判别式大于0时，求两个实数根
void realRoots(double a, double b, double discriminant) {
    double x1 = (-b + sqrt(discriminant)) / (2 * a);
    double x2 = (-b - sqrt(discriminant)) / (2 * a);
    cout << fixed << setprecision(3) << "x1=" << x1 << " x2=" << x2 << endl;
}

// 当判别式等于0时，求一个实数根
void equalRoots(double a, double b) {
    double x = -b / (2 * a);
    cout << fixed << setprecision(3) << "x1=" << x << " x2=" << x << endl;
}

// 当判别式小于0时，求两个复数根
void complexRoots(double a, double b, double discriminant) {
    double realPart = -b / (2 * a);
    double imaginaryPart = sqrt(-discriminant) / (2 * a);
    cout << fixed << setprecision(3) << "x1=" << realPart << "+" << imaginaryPart << "i x2=" << realPart << "-" << imaginaryPart << "i" << endl;
}

int main() {
    double a, b, c;
    cin >> a >> b >> c;

    if (a == 0) {
        // 处理a为0的情况，退化为一次方程
        if (b != 0) {
            double x = -c / b;
            cout << fixed << setprecision(3) << "x=" << x << endl;
        } else {
            if (c == 0) {
                cout << "Infinite solutions" << endl;
            } else {
                cout << "No solution" << endl;
            }
        }
        return 0;
    }

    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        realRoots(a, b, discriminant);
    } else if (discriminant == 0) {
        equalRoots(a, b);
    } else {
        complexRoots(a, b, discriminant);
    }

    return 0;
}