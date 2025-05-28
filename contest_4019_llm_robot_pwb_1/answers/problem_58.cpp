/* 文件头注释：说明核心算法名称和关键技术 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    cin.ignore(); // 清除输入缓冲区中的换行符

    while (T--) {
        string password;
        getline(cin, password); // 读取整行密码，包括空格

        string decryptedPassword;
        for (char ch : password) {
            if (!isdigit(ch)) { // 如果字符不是数字，则保留
                decryptedPassword += ch;
            }
        }

        cout << decryptedPassword << endl;
    }

    return 0;
}