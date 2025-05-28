#include <iostream>
#include <vector>
#include <string>
#include <numeric> // Included for completeness, though manual prefix sum loop is typical

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s;
    std::cin >> s;
    int n = s.length();

    std::vector<int> prefR(n + 1, 0);
    std::vector<int> prefG(n + 1, 0);
    std::vector<int> prefB(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        prefR[i+1] = prefR[i];
        prefG[i+1] = prefG[i];
        prefB[i+1] = prefB[i];
        if (s[i] == 'R') {
            prefR[i+1]++;
        } else if (s[i] == 'G') {
            prefG[i+1]++;
        } else if (s[i] == 'B') {
            prefB[i+1]++;
        }
    }

    int q;
    std::cin >> q;
    std::string result_str = "";
    result_str.reserve(q); // Pre-allocate memory for efficiency

    for (int k = 0; k < q; ++k) {
        int l_query, r_query; // L, R are 1-indexed in problem description
        std::cin >> l_query >> r_query;

        // Calculate counts in the range [L, R] (1-indexed)
        // Corresponding to 0-indexed string S[l_query-1 ... r_query-1]
        // Count in S[0...r_query-1] - Count in S[0...l_query-2]
        int countR = prefR[r_query] - prefR[l_query-1];
        int countG = prefG[r_query] - prefG[l_query-1];
        int countB = prefB[r_query] - prefB[l_query-1];

        int pR = countR % 2;
        int pG = countG % 2;
        int pB = countB % 2;

        if ((pR == 1 && pG == 0 && pB == 0) || (pR == 0 && pG == 1 && pB == 1)) {
            result_str += 'Y';
        } else {
            result_str += 'N';
        }
    }

    std::cout << result_str << std::endl;

    return 0;
}