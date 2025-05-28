#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

// Function to check if a string is a palindrome
bool is_palindrome_str(const std::string& s) {
    // An empty string can be a valid palindrome component (e.g. if P or suffix is empty)
    // but for this problem, P and suffix/prefix derived from s1 are non-empty in cases 2 and 3.
    // However, the P_candidate or prefix_s1 string itself could be checked.
    if (s.empty()) {
      return true; // An empty part of a string (e.g. an empty prefix or suffix) is palindromic
    }
    std::string temp = s;
    std::reverse(temp.begin(), temp.end());
    return s == temp;
}

std::string reverse_string(const std::string& s) {
    std::string reversed_s = s;
    std::reverse(reversed_s.begin(), reversed_s.end());
    return reversed_s;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<std::string> words(n);
    std::unordered_map<std::string, int> word_to_idx;
    for (int i = 0; i < n; ++i) {
        std::cin >> words[i];
        word_to_idx[words[i]] = i;
    }

    int max_len = 0;

    for (int i = 0; i < n; ++i) {
        const std::string& s1 = words[i];
        int len_s1 = s1.length();

        // Case 1: s1 + s2 where s2 = reverse(s1)
        // This covers pairs like ("ab", "ba") -> "abba"
        std::string rev_s1 = reverse_string(s1);
        if (word_to_idx.count(rev_s1)) {
            int idx_s2 = word_to_idx.at(rev_s1);
            if (idx_s2 != i) { // Ensure they are different strings
                max_len = std::max(max_len, len_s1 + (int)rev_s1.length());
            }
        }

        // Case 2: s1 = P + suffix_s1. We find s2 = reverse(suffix_s1).
        // Resulting palindrome: P + suffix_s1 + reverse(suffix_s1) (which is s1 + s2)
        // P must be a non-empty palindrome prefix of s1.
        // suffix_s1 must be non-empty.
        // Loop j for the length of P.
        for (int j = 1; j < len_s1; ++j) { 
            std::string p_candidate = s1.substr(0, j); // P
            if (is_palindrome_str(p_candidate)) {
                std::string suffix_s1 = s1.substr(j); // suffix_s1 (non-empty as j < len_s1)
                std::string s2_target = reverse_string(suffix_s1);
                if (word_to_idx.count(s2_target)) {
                    int idx_s2 = word_to_idx.at(s2_target);
                    if (idx_s2 != i) {
                        max_len = std::max(max_len, len_s1 + (int)s2_target.length());
                    }
                }
            }
        }

        // Case 3: s1 = prefix_s1 + P. We find s2 = reverse(prefix_s1).
        // Resulting palindrome: reverse(prefix_s1) + prefix_s1 + P (which is s2 + s1)
        // P must be a non-empty palindrome suffix of s1.
        // prefix_s1 must be non-empty.
        // Loop k for the length of prefix_s1.
        for (int k = 1; k < len_s1; ++k) { 
            std::string prefix_s1 = s1.substr(0, k); // prefix_s1 (non-empty as k >= 1)
            std::string p_candidate = s1.substr(k);  // P (non-empty as k < len_s1)
            if (is_palindrome_str(p_candidate)) {
                std::string s2_target = reverse_string(prefix_s1);
                if (word_to_idx.count(s2_target)) {
                    int idx_s2 = word_to_idx.at(s2_target);
                    if (idx_s2 != i) {
                        max_len = std::max(max_len, (int)s2_target.length() + len_s1);
                    }
                }
            }
        }
    }

    std::cout << max_len << std::endl;

    return 0;
}