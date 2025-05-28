/* 文件头注释：使用埃拉托斯特尼筛法生成素数表，并验证哥德巴赫猜想 */
#include <bits/stdc++.h>
using namespace std;

// 生成2000以内的素数表
vector<int> generatePrimes(int limit) {
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= limit; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                isPrime[j] = false;
            }
        }
    }
    vector<int> primes;
    for (int i = 2; i <= limit; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

int main() {
    int limit = 2000;
    vector<int> primes = generatePrimes(limit);

    // 遍历所有大于2的偶数
    for (int even = 4; even <= limit; even += 2) {
        // 遍历素数表，找到两个素数之和等于当前偶数
        for (int prime : primes) {
            if (prime > even / 2) break; // 由于素数按升序排列，超过一半后无需继续
            int otherPrime = even - prime;
            if (binary_search(primes.begin(), primes.end(), otherPrime)) {
                cout << even << "=" << prime << "+" << otherPrime << endl;
                break;
            }
        }
    }

    return 0;
}