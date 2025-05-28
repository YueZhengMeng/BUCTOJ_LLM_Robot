/* 
   Author: Expert Competitive Programmer
   Algorithm: Simulation with undo via stack of edit operations
   Key techniques: string manipulation, stack for undo
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string cmd;
    string text;            // current editor text
    bool isLower = true;    // true = lowercase mode, false = uppercase mode

    // history of edit operations: (1, c) for insertion of c; (2, c) for deletion of c
    vector<pair<int,char>> history;
    history.reserve(n);

    while (n--) {
        cin >> cmd;
        if (cmd == "SPACE") {
            // Insert space
            text.push_back(' ');
            history.emplace_back(1, ' ');
        }
        else if (cmd == "BACKSPACE") {
            if (!text.empty()) {
                char c = text.back();
                text.pop_back();
                history.emplace_back(2, c);
            }
            // else do nothing (no history record)
        }
        else if (cmd == "CTRL+Z") {
            if (!history.empty()) {
                auto [opType, c] = history.back();
                history.pop_back();
                if (opType == 1) {
                    // undo insertion
                    text.pop_back();
                } else {
                    // undo deletion
                    text.push_back(c);
                }
            }
        }
        else if (cmd == "CAPSLOCK") {
            isLower = !isLower;
        }
        else if (cmd.rfind("SHIFT+", 0) == 0) {
            // SHIFT + single letter
            char letter = cmd[6];
            char out;
            if (isLower) {
                // current mode would have inserted lowercase, so SHIFT gives uppercase
                out = letter;  // letter is uppercase already
            } else {
                // current mode uppercase, so SHIFT gives lowercase
                out = char(letter - 'A' + 'a');
            }
            text.push_back(out);
            history.emplace_back(1, out);
        }
        else {
            // Single letter A-Z
            char letter = cmd[0];
            char out;
            if (isLower) {
                out = char(letter - 'A' + 'a');
            } else {
                out = letter;
            }
            text.push_back(out);
            history.emplace_back(1, out);
        }
    }

    // Guaranteed non-empty and no trailing spaces in final text
    cout << text << "\n";
    return 0;
}