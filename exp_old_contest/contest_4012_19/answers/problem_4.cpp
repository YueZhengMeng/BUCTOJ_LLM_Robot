/* 
   Algorithm: Sign check + case-insensitive string comparison
   Key steps:
   1. Read x, y
   2. Determine expected = "yes" if same sign, else "no"
   3. Read user's answer, convert to lowercase
   4. Compare and print "ok" or "wa"
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, y;
    string userAns;
    cin >> x >> y >> userAns;

    // Determine correct answer
    bool sameSign = (x > 0 && y > 0) || (x < 0 && y < 0);
    string correctAns = sameSign ? "yes" : "no";

    // Convert user answer to lowercase
    for (char &c : userAns) {
        c = tolower(c);
    }

    // Compare and output result
    if (userAns == correctAns) {
        cout << "ok\n";
    } else {
        cout << "wa\n";
    }

    return 0;
}