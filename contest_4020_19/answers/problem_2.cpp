/* 
  Algorithm: Minimize stamps = 2n + min_{1<=a<=sqrt(n)}(a + ceil(n/a))
  by scanning a up to sqrt(n).
*/
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;

    long long bestSum = LLONG_MAX;
    long long r = floor(sqrt((long double)n));
    for(long long a = 1; a <= r; ++a) {
        long long b = (n + a - 1) / a;  // ceil(n/a)
        bestSum = min(bestSum, a + b);
    }

    // total stamps = 2n + best(a+b)
    long long answer = 2LL * n + bestSum;
    cout << answer << "\n";

    return 0;
}