/* 文件头注释：利用完全二叉搜索树的性质，快速计算子树的最小值和最大值 */
#include <bits/stdc++.h>
using namespace std;

// 计算以X为根的子树中的最小值
long long findMin(long long X) {
    long long minVal = X;
    while (minVal * 2 <= 2e31 - 1) {
        minVal *= 2;
    }
    return minVal;
}

// 计算以X为根的子树中的最大值
long long findMax(long long X) {
    long long maxVal = X;
    while (maxVal * 2 + 1 <= 2e31 - 1) {
        maxVal = maxVal * 2 + 1;
    }
    return maxVal;
}

int main() {
    int N;
    cin >> N;
    while (N--) {
        long long X;
        cin >> X;
        long long minVal = findMin(X);
        long long maxVal = findMax(X);
        cout << minVal << " " << maxVal << endl;
    }
    return 0;
}