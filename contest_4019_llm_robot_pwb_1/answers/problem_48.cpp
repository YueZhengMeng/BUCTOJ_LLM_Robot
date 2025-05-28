/* 文件头注释：特工密码解码程序，核心算法为逆向模拟加密过程 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int K;
    cin >> K; // 读取计算用例数
    while (K--) {
        int key;
        string ciphertext;
        cin >> key >> ciphertext; // 读取密钥和密文
        string plaintext;
        for (int i = 0; i < ciphertext.length(); ++i) {
            // 将密文字符转换为对应的编码
            int c = 0;
            if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
                c = ciphertext[i] - 'a';
            } else if (ciphertext[i] == ',') {
                c = 26;
            } else if (ciphertext[i] == '.') {
                c = 27;
            } else if (ciphertext[i] == '-') {
                c = 28;
            } else if (ciphertext[i] == '_') {
                c = 29;
            }
            // 逆向推导明文编码
            int p = (c - i + key) % 30;
            if (p < 0) p += 30;
            // 将明文编码转换为对应的字符
            char plainchar;
            if (p >= 0 && p <= 25) {
                plainchar = 'a' + p;
            } else if (p == 26) {
                plainchar = ',';
            } else if (p == 27) {
                plainchar = '.';
            } else if (p == 28) {
                plainchar = '-';
            } else if (p == 29) {
                plainchar = '_';
            }
            plaintext.push_back(plainchar);
        }
        cout << plaintext << endl; // 输出解码后的明文
    }
    return 0;
}