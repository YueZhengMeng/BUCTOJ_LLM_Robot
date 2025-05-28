/* 文件头注释：模拟文本编辑器的操作，使用栈记录历史操作 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    string text = "";
    bool capsLock = false; // 初始为小写状态
    stack<pair<string, char>> history; // 用于记录历史操作及其类型

    for (int i = 0; i < n; ++i) {
        string command;
        cin >> command;

        if (command.size() == 1 && isupper(command[0])) {
            // 单个大写字母指令
            char c = capsLock ? command[0] : tolower(command[0]);
            text += c;
            history.push({"ADD", c});
        } else if (command.substr(0, 6) == "SHIFT+") {
            // SHIFT+[A-Z] 指令
            char c = capsLock ? tolower(command[6]) : toupper(command[6]);
            text += c;
            history.push({"ADD", c});
        } else if (command == "SPACE") {
            // SPACE 指令
            text += ' ';
            history.push({"ADD", ' '});
        } else if (command == "BACKSPACE") {
            // BACKSPACE 指令
            if (!text.empty()) {
                history.push({"DEL", text.back()});
                text.pop_back();
            }
        } else if (command == "CTRL+Z") {
            // CTRL+Z 指令
            if (!history.empty()) {
                auto lastOp = history.top();
                history.pop();
                if (lastOp.first == "ADD") {
                    text.pop_back();
                } else if (lastOp.first == "DEL") {
                    text += lastOp.second;
                }
            }
        } else if (command == "CAPSLOCK") {
            // CAPSLOCK 指令
            capsLock = !capsLock;
        }
    }

    cout << text << endl;
    return 0;
}