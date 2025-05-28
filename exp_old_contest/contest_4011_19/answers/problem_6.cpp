/* 
   Algorithm: Lexicographical ranking of subsets via combinatorial counts.
   Key techniques: BigInteger (base 1e9), precompute powers of two, range-sum trick.
*/
#include <bits/stdc++.h>
using namespace std;

// Big integer in base 1e9
struct BigInt {
    static const uint32_t BASE = 1000000000;
    vector<uint32_t> a; // little-endian limbs

    BigInt(uint64_t v = 0) { *this = v; }

    BigInt& operator=(uint64_t v) {
        a.clear();
        if (v == 0) return *this;
        while (v) {
            a.push_back(v % BASE);
            v /= BASE;
        }
        return *this;
    }

    bool isZero() const { return a.empty(); }

    // trim leading zeros
    void trim() {
        while (!a.empty() && a.back() == 0) a.pop_back();
    }

    // this += other
    BigInt& operator+=(const BigInt &other) {
        uint64_t carry = 0;
        size_t n = max(a.size(), other.a.size());
        if (a.size() < n) a.resize(n, 0);
        for (size_t i = 0; i < n; i++) {
            uint64_t sum = carry + a[i] + (i < other.a.size() ? other.a[i] : 0);
            a[i] = sum % BASE;
            carry = sum / BASE;
        }
        if (carry) a.push_back(carry);
        return *this;
    }

    // assume *this >= other
    BigInt& operator-=(const BigInt &other) {
        int64_t carry = 0;
        for (size_t i = 0; i < other.a.size() || carry; i++) {
            int64_t sub = int64_t(a[i]) - (i < other.a.size() ? other.a[i] : 0) - carry;
            if (sub < 0) {
                sub += BASE;
                carry = 1;
            } else carry = 0;
            a[i] = uint32_t(sub);
        }
        trim();
        return *this;
    }

    // multiply by small (2)
    BigInt& mul2() {
        uint64_t carry = 0;
        for (size_t i = 0; i < a.size(); i++) {
            uint64_t cur = uint64_t(a[i]) * 2 + carry;
            a[i] = cur % BASE;
            carry = cur / BASE;
        }
        if (carry) a.push_back(carry);
        return *this;
    }

    // print decimal
    string toString() const {
        if (a.empty()) return "0";
        string s = to_string(a.back());
        char buf[16];
        for (int i = (int)a.size() - 2; i >= 0; i--) {
            sprintf(buf, "%09u", a[i]);
            s += buf;
        }
        return s;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    vector<int> A(k);
    for (int i = 0; i < k; i++) {
        cin >> A[i];
    }

    // Precompute pw[i] = 2^i for i=0..n
    vector<BigInt> pw(n+2);
    pw[0] = 1;
    for (int i = 1; i <= n; i++) {
        pw[i] = pw[i-1];
        pw[i].mul2();
    }

    // rank (0-based count of subsets lex less than A)
    BigInt rank(0);

    // Helper to add sum_{b=L..R} 2^(n-b) if L<=R
    auto addRange = [&](int L, int R){
        if (L > R) return;
        // sum = (2^(n-L+1)-1) - (2^(n-R) -1) = pw[n-L+1] - pw[n-R]
        BigInt tmp = pw[n - L + 1];
        tmp -= BigInt(1);
        BigInt tmp2 = pw[n - R];
        tmp2 -= BigInt(1);
        tmp -= tmp2;
        rank += tmp;
    };

    // Position 1: first element
    addRange(1, A[0] - 1);
    // count exact prefix subset {A[0]}
    rank += BigInt(1);

    // Positions 2..k
    for (int i = 1; i < k; i++) {
        int prev = A[i-1];
        int cur  = A[i];
        addRange(prev + 1, cur - 1);
        // count exact prefix subset {A[0]..A[i]}
        rank += BigInt(1);
    }

    // rank is already 1-based (we counted the subset itself at last step)
    cout << rank.toString() << "\n";
    return 0;
}