/* 文件头注释：提取字符串中的元音字母 */
#include <bits/stdc++.h>
using namespace std;

// 判断字符是否为元音字母
bool isVowel(char ch) {
    ch = tolower(ch); // 统一转换为小写字母
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

int main() {
    string input;
    getline(cin, input); // 读取一行输入
    string vowels;
    
    // 遍历输入字符串，提取元音字母
    for (char ch : input) {
        if (isVowel(ch)) {
            vowels.push_back(ch);
        }
    }
    
    // 输出结果
    cout << vowels << endl;
    return 0;
}