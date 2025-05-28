/* 
   Magic Conversion (呆毛王的魔力转换)
   Map each digit to '#' if odd, '*' if even. 
   Simple one-pass string transformation.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string n;
    cin >> n;

    string result;
    result.reserve(n.size());

    for (char c : n) {
        int digit = c - '0';
        if (digit % 2 == 0)
            result.push_back('*');
        else
            result.push_back('#');
    }

    cout << result << "\n";
    return 0;
}