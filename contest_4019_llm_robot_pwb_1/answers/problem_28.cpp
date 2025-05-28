/* 文件头注释：统计字符串中字母、数字、空格和其他字符的数量 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    getline(cin, s); // 读取一行字符串，包括空格
    int letterCount = 0, digitCount = 0, spaceCount = 0, otherCount = 0;

    for (char ch : s) {
        if (isalpha(ch)) {
            letterCount++;
        } else if (isdigit(ch)) {
            digitCount++;
        } else if (isspace(ch)) {
            spaceCount++;
        } else {
            otherCount++;
        }
    }

    cout << letterCount << " " << digitCount << " " << spaceCount << " " << otherCount << endl;
    return 0;
}