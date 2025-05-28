/* 文件头注释：计算圆的周长、面积，圆球的表面积、体积，以及圆柱的体积 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    float r, h;
    const float PI = 3.14;

    // 输入圆半径r和圆柱高h
    scanf("%f %f", &r, &h);

    // 计算圆周长C1
    float C1 = 2 * PI * r;
    // 计算圆面积Sa
    float Sa = PI * r * r;
    // 计算圆球表面积Sb
    float Sb = 4 * PI * r * r;
    // 计算圆球体积Va
    float Va = (4.0 / 3) * PI * r * r * r;
    // 计算圆柱体积Vb
    float Vb = PI * r * r * h;

    // 输出结果，保留两位小数，不四舍五入
    printf("C1=%.2f\n", C1);
    printf("Sa=%.2f\n", Sa);
    printf("Sb=%.2f\n", Sb);
    printf("Va=%.2f\n", Va);
    printf("Vb=%.2f\n", Vb);

    return 0;
}