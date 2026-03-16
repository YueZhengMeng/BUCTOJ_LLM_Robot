/* BST construction and preorder traversal */
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Insert key into BST recursively
TreeNode* insert(TreeNode* root, int key) {
    if (!root) return new TreeNode(key);
    if (key < root->val)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);
    return root;
}

// Preorder traversal, storing result in vector
void preorder(TreeNode* root, vector<int>& res) {
    if (!root) return;
    res.push_back(root->val);
    preorder(root->left, res);
    preorder(root->right, res);
}

int main() {
    int n;
    while (cin >> n) {               // Process each test case until EOF
        TreeNode* root = nullptr;
        for (int i = 0; i < n; i++) {
            int key;
            cin >> key;
            root = insert(root, key);   // Build BST step by step
        }
        vector<int> traversal;
        preorder(root, traversal);      // Get preorder sequence
        for (size_t i = 0; i < traversal.size(); i++) {
            if (i) cout << ' ';
            cout << traversal[i];
        }
        cout << endl;                   // Newline after each case
    }
    return 0;
}