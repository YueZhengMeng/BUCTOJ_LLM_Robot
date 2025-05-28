/* 文件头注释：模拟浏览器导航功能，使用两个栈实现 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    stack<string> backStack;  // 后向栈，存储可以后退的页面
    stack<string> forwardStack;  // 前向栈，存储可以前进的页面
    string currentPage = "***###.acm.org/";  // 初始页面

    string command;
    while (cin >> command) {
        if (command == "QUIT") {
            break;
        } else if (command == "VISIT") {
            string url;
            cin >> url;
            backStack.push(currentPage);  // 将当前页面压入后向栈
            currentPage = url;  // 更新当前页面
            while (!forwardStack.empty()) {  // 清空前向栈
                forwardStack.pop();
            }
            cout << currentPage << endl;
        } else if (command == "BACK") {
            if (backStack.empty()) {
                cout << "Ignored" << endl;
            } else {
                forwardStack.push(currentPage);  // 将当前页面压入前向栈
                currentPage = backStack.top();  // 从后向栈弹出页面作为当前页面
                backStack.pop();
                cout << currentPage << endl;
            }
        } else if (command == "FORWARD") {
            if (forwardStack.empty()) {
                cout << "Ignored" << endl;
            } else {
                backStack.push(currentPage);  // 将当前页面压入后向栈
                currentPage = forwardStack.top();  // 从前向栈弹出页面作为当前页面
                forwardStack.pop();
                cout << currentPage << endl;
            }
        }
    }

    return 0;
}