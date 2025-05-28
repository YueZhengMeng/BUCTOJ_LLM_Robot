/* 文件头注释：判断乘号漂移问题，通过枚举所有可能的乘号位置并计算乘积 */
#include <bits/stdc++.h>
using namespace std;

// 计算字符串表示的数值
long long calculateValue(const string& s) {
    long long value = 0;
    for (char ch : s) {
        value = value * 10 + (ch - '0');
    }
    return value;
}

// 判断是否可以进行乘号漂移
bool canShiftMultiply(const string& s) {
    int n = s.length();
    int starPos = s.find('*');
    string leftOriginal = s.substr(0, starPos);
    string rightOriginal = s.substr(starPos + 1);
    long long originalValue = calculateValue(leftOriginal) * calculateValue(rightOriginal);
    
    // 枚举所有可能的乘号位置
    for (int i = 1; i < n - 1; ++i) {
        if (i == starPos) continue; // 跳过原始位置
        string leftStr = s.substr(0, i);
        string rightStr = s.substr(i + 1);
        long long leftValue = calculateValue(leftStr);
        long long rightValue = calculateValue(rightStr);
        if (leftValue * rightValue == originalValue) {
            // 检查前导零是否一致
            if (leftStr == leftOriginal && rightStr == rightOriginal) continue;
            return true;
        }
    }
    return false;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        if (canShiftMultiply(s)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}