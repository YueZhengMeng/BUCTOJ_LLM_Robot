/* 文件头注释：动态规划模拟呆唯的游戏过程 */
#include <bits/stdc++.h>
using namespace std;

// 定义矩阵结构体
struct Matrix {
    double data[2][2];
    Matrix() {
        memset(data, 0, sizeof(data));
    }
};

// 矩阵乘法
Matrix multiply(const Matrix& a, const Matrix& b) {
    Matrix res;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                res.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return res;
}

// 矩阵快速幂
Matrix matrix_pow(Matrix a, int n) {
    Matrix res;
    // 初始化为单位矩阵
    res.data[0][0] = res.data[1][1] = 1.0;
    while (n > 0) {
        if (n & 1) {
            res = multiply(res, a);
        }
        a = multiply(a, a);
        n >>= 1;
    }
    return res;
}

int main() {
    double p, q;
    int x;
    cin >> p >> q >> x;

    // 构建状态转移矩阵
    Matrix trans;
    // 从围棋转移到云顶之奕的概率是p，继续围棋的概率是1-p
    trans.data[0][0] = 1 - p;
    trans.data[0][1] = p;
    // 从云顶之奕转移到围棋的概率是q，继续云顶之奕的概率是1-q
    trans.data[1][0] = q;
    trans.data[1][1] = 1 - q;

    // 计算转移矩阵的(x-1)次幂
    Matrix result = matrix_pow(trans, x - 1);

    // 初始状态：第一局是围棋
    double prob_go = 1.0;
    double prob_cloud = 0.0;

    // 计算第x局的概率
    double final_prob = prob_go * result.data[0][0] + prob_cloud * result.data[1][0];

    // 输出结果，保留10位小数
    cout << fixed << setprecision(10) << final_prob << endl;

    return 0;
}