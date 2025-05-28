/* 文件头注释：JSON格式化程序，使用递归处理嵌套JSON对象 */
#include <bits/stdc++.h>
using namespace std;

// 递归函数，用于格式化JSON字符串
string formatJSON(const string& json, int indentLevel = 0) {
    string result;
    int i = 0;
    int n = json.length();
    string indent(indentLevel * 4, ' '); // 当前缩进

    while (i < n) {
        char ch = json[i];
        if (ch == '{') {
            result += "{\n";
            indentLevel++;
            indent = string(indentLevel * 4, ' ');
            i++;
        } else if (ch == '}') {
            indentLevel--;
            indent = string(indentLevel * 4, ' ');
            result += "\n" + indent + "}";
            i++;
        } else if (ch == ',') {
            result += ",\n" + indent;
            i++;
        } else if (ch == ':') {
            result += ": ";
            i++;
        } else {
            result += ch;
            i++;
        }
    }

    return result;
}

int main() {
    string json;
    getline(cin, json); // 读取输入的JSON字符串
    string formattedJSON = formatJSON(json);
    cout << formattedJSON << endl;
    return 0;
}