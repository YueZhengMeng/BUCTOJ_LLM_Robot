/* Level-order traversal via sorting by (depth, path) */
#include <bits/stdc++.h>
using namespace std;

// Comparator: first by path length (depth), then by path string lexicographically
bool cmp(const pair<int, string>& a, const pair<int, string>& b) {
    if (a.second.size() != b.second.size())
        return a.second.size() < b.second.size();
    return a.second < b.second;
}

int main() {
    vector<pair<int, string>> nodes; // stores (value, path) for the current tree
    string token;
    while (cin >> token) {
        if (token == "()") {
            // End of current tree: sort and output
            if (!nodes.empty()) {
                sort(nodes.begin(), nodes.end(), cmp);
                for (size_t i = 0; i < nodes.size(); ++i) {
                    if (i > 0) cout << " ";
                    cout << nodes[i].first;
                }
                cout << endl;
                nodes.clear();
            }
        } else {
            // Parse token of the form "(value,path)"
            string content = token.substr(1, token.size() - 2); // strip '(' and ')'
            size_t comma = content.find(',');
            string val_str = content.substr(0, comma);
            string path = content.substr(comma + 1);
            int val = stoi(val_str);
            nodes.push_back({val, path});
        }
    }
    return 0;
}