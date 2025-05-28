/* 文件头注释：格式化输出实数 */
#include <cstdio>  // 使用printf进行格式化输出

int main() {
    float num;
    scanf("%f", &num);  // 读取输入的实数

    // 第一行：输出一个实数
    printf("%6.2f\n", num);

    // 第二行：输出两个实数，用空格分隔
    printf("%6.2f %6.2f\n", num, num);

    // 第三行：输出三个实数，用空格分隔
    printf("%6.2f %6.2f %6.2f\n", num, num, num);

    return 0;
}