/* 文件头注释：BMI体重计算，关键技术：单位转换和四舍五入 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    double height_cm, bmi;
    cin >> height_cm >> bmi;
    
    // 将身高从厘米转换为米
    double height_m = height_cm / 100.0;
    
    // 计算体重
    double weight = bmi * height_m * height_m;
    
    // 四舍五入保留三位小数
    cout << fixed << setprecision(3) << weight << endl;
    
    return 0;
}