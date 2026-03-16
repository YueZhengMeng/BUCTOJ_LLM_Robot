/* Linear List Operations using Vector
   Supports insert, delete, search, and show operations */
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<string> names;  // Store the list of names
    string command;        // Command: insert, delete, show, search
    
    while (cin >> command) {
        if (command == "insert") {
            int pos;
            string name;
            cin >> pos >> name;
            // Insert at position pos-1 (convert 1-indexed to 0-indexed)
            names.insert(names.begin() + (pos - 1), name);
        }
        else if (command == "delete") {
            string name;
            cin >> name;
            // Find and erase the name
            for (auto it = names.begin(); it != names.end(); ++it) {
                if (*it == name) {
                    names.erase(it);
                    break;
                }
            }
        }
        else if (command == "show") {
            // Print all names separated by space
            for (size_t i = 0; i < names.size(); ++i) {
                if (i > 0) cout << " ";
                cout << names[i];
            }
            cout << endl;  // Always print newline (blank if empty)
        }
        else if (command == "search") {
            string name;
            cin >> name;
            // Find index (1-indexed)
            for (size_t i = 0; i < names.size(); ++i) {
                if (names[i] == name) {
                    cout << i + 1 << endl;
                    break;
                }
            }
        }
    }
    
    return 0;
}