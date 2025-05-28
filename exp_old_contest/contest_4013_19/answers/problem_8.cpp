/* 
   Find the missing permutation by XORing all input permutations 
   and XORing that with the XOR of all permutations (which is 0 for n>=3, 
   and 0^1=1 for n=2 in each position).
*/
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    // For n == 2, (n-1)! is odd => xor of digits {0,1} at each position = 1
    int xor_all_perms = (n == 2 ? 1 : 0);

    // Precompute n! as an integer
    long long total = 1;
    for(int i = 2; i <= n; i++){
        total *= i;
    }

    vector<int> xor_pos(n, 0);
    string s;
    s.reserve(n);

    // Read (n! - 1) distinct permutations and XOR their digits position-wise
    for(long long i = 0; i < total - 1; i++){
        cin >> s;
        for(int j = 0; j < n; j++){
            xor_pos[j] ^= (s[j] - '0');
        }
    }

    // Recover the missing permutation by XORing with xor_all_perms
    string missing(n, '0');
    for(int j = 0; j < n; j++){
        int digit = xor_pos[j] ^ xor_all_perms;
        missing[j] = char('0' + digit);
    }

    cout << missing << "\n";
    return 0;
}