/* 
  Algorithm: Direct parsing of space-separated hex tokens 
  Technique: stoi with base 16, string manipulation
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    // Read the entire line of hex codes
    if (!getline(cin, line)) return 0;

    istringstream iss(line);
    string hexToken;
    string result;
    
    // Process each hex token
    while (iss >> hexToken) {
        // Convert hex string to integer (base 16), then to char
        int val = stoi(hexToken, nullptr, 16);
        result.push_back(static_cast<char>(val));
    }
    
    // Output the decoded ASCII string
    cout << result;
    return 0;
}