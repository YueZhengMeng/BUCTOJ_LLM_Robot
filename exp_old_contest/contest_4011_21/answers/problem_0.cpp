/* 文件头注释：数字转中文拼音，逐位处理 */
#include <bits/stdc++.h>
using namespace std;

// 数字对应的拼音
const string num_to_pinyin[] = {"ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};
// 单位对应的拼音
const string unit_to_pinyin[] = {"", "shi", "bai", "qian", "wan", "shi wan", "bai wan", "qian wan", "yi"};

string numberToPinyin(int num) {
    if (num == 0) return num_to_pinyin[0];
    
    string result;
    int pos = 0; // 当前处理的位数
    bool has_zero = false; // 标记是否有连续的零
    
    while (num > 0) {
        int digit = num % 10;
        num /= 10;
        
        if (digit == 0) {
            if (!has_zero && pos != 0) {
                result = num_to_pinyin[0] + " " + result;
                has_zero = true;
            }
        } else {
            string temp = num_to_pinyin[digit];
            if (pos > 0) {
                temp += " " + unit_to_pinyin[pos];
            }
            result = temp + " " + result;
            has_zero = false;
        }
        
        pos++;
    }
    
    // 去除末尾的空格
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    
    // 处理10-19的特殊情况
    if (result.size() >= 7 && result.substr(0, 7) == "yi shi ") {
        result = result.substr(3);
    }
    
    return result;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int num;
        cin >> num;
        cout << numberToPinyin(num) << endl;
    }
    return 0;
}