/* 
 * Algorithm: Recursive descent parse + pretty-print 
 * Techniques: 
 *   - Build a tree of Nodes (string or object)
 *   - Two‐phase: parse then format with indentation
 */
#include <bits/stdc++.h>
using namespace std;

// A Node is either a plain string, or an object (vector of (key, Node) pairs).
struct Node {
    bool isString;
    string s;
    vector<pair<string, Node>> obj;
};

string input;
int pos = 0;

// Parse a JSON string: assumes input[pos] == '"'
string parseString() {
    pos++;  // skip opening '"'
    string res;
    while (pos < (int)input.size() && input[pos] != '"') {
        res.push_back(input[pos++]);
    }
    pos++;  // skip closing '"'
    return res;
}

// Forward declare
Node parseValue();

// Parse an object: assumes input[pos] == '{'
Node parseObject() {
    Node node;
    node.isString = false;
    pos++;  // skip '{'
    // Check for empty object
    if (input[pos] == '}') {
        pos++;  // skip '}'
        return node;
    }
    // Otherwise parse key:value pairs
    while (true) {
        // parse key
        string key = parseString();
        // skip ':'
        pos++;
        // parse value
        Node val = parseValue();
        node.obj.emplace_back(key, move(val));
        // if comma, consume and continue; else must be '}'
        if (input[pos] == ',') {
            pos++;
            continue;
        } else {
            pos++; // skip '}'
            break;
        }
    }
    return node;
}

// Parse a value: either a string or an object
Node parseValue() {
    if (input[pos] == '"') {
        Node n;
        n.isString = true;
        n.s = parseString();
        return n;
    } else {
        return parseObject();
    }
}

// Print an object which appears as a value (i.e., inline after ": ")
void printObjectValue(const vector<pair<string, Node>>& obj, int indent);

// Print a node at given indent
void printNode(const Node& node, int indent) {
    if (node.isString) {
        // Print quoted string
        cout << '"' << node.s << '"';
    } else {
        // Print nested object inline
        printObjectValue(node.obj, indent);
    }
}

// Print an object when it's used as a value (no leading indent before '{')
void printObjectValue(const vector<pair<string, Node>>& obj, int indent) {
    // opening brace
    cout << '{' << '\n';
    int n = obj.size();
    for (int i = 0; i < n; i++) {
        // print key line
        cout << string(indent + 4, ' ')
             << '"' << obj[i].first << "\": ";
        // print its value
        printNode(obj[i].second, indent + 4);
        if (i + 1 < n) cout << ',';
        cout << '\n';
    }
    // closing brace at 'indent' spaces
    cout << string(indent, ' ') << '}';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read the single-line JSON
    getline(cin, input);

    // Parse into a tree
    pos = 0;
    Node root = parseObject();

    // Pretty-print the root object
    // Opening brace at indent 0
    cout << "{\n";
    int m = root.obj.size();
    for (int i = 0; i < m; i++) {
        // each key at indent 4
        cout << string(4, ' ')
             << '"' << root.obj[i].first << "\": ";
        printNode(root.obj[i].second, 4);
        if (i + 1 < m) cout << ',';
        cout << '\n';
    }
    // Closing brace at indent 0
    cout << "}\n";

    return 0;
}