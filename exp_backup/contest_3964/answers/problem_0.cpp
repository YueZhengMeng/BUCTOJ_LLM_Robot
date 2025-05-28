#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
constexpr int N = 23333333;
const double H = 11625907.5798;

double calculateEntropy(int k) {
    double p0 = 1.0 * k / N;
    double p1 = 1.0 * (N - k) / N;
    if (p0 == 0 || p1 == 0) return 0;
    return - (p0 * log2(p0) + p1 * log2(p1)) * N;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int left = 0, right = N / 2;
    int result = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        double entropy = calculateEntropy(mid);
        if (fabs(entropy - H) < 1e-4) {
            result = mid;
            break;
        } else if (entropy < H) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    cout << result << endl;
    return 0;
}