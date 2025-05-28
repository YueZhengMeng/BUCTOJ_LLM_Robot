/* 文件头注释：判断两个整数的符号是否相同，并验证参赛者输出是否正确 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int x, y;
    string userAnswer;
    
    // 输入两个整数
    cin >> x >> y;
    // 输入参赛者的答案
    cin >> userAnswer;
    
    // 判断两个整数的符号是否相同
    bool isSameSign = (x > 0 && y > 0) || (x < 0 && y < 0);
    
    // 将参赛者的答案转换为小写
    transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(), ::tolower);
    
    // 判断参赛者的答案是否正确
    if ((isSameSign && userAnswer == "yes") || (!isSameSign && userAnswer == "no")) {
        cout << "ok" << endl;
    } else {
        cout << "wa" << endl;
    }
    
    return 0;
}