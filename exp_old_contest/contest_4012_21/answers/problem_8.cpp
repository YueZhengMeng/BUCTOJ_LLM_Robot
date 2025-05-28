/* 文件头注释：使用双向BFS算法寻找从1到p/q的最短路径 */
#include <bits/stdc++.h>
using namespace std;

// 定义有理数结构体
struct Rational {
    long long p, q;
    Rational(long long p = 0, long long q = 1) : p(p), q(q) {}
    bool operator==(const Rational& other) const {
        return p == other.p && q == other.q;
    }
    bool operator<(const Rational& other) const {
        return p * other.q < other.p * q;
    }
};

// 定义节点结构体
struct Node {
    Rational val;
    int direction; // 0: from start, 1: from target
    Node(Rational val, int direction) : val(val), direction(direction) {}
};

// 计算最大公约数
long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

// 双向BFS函数
string bidirectional_bfs(Rational target) {
    queue<Node> q;
    unordered_map<long long, unordered_map<long long, string>> visited_from_start;
    unordered_map<long long, unordered_map<long long, string>> visited_from_target;

    q.push(Node(Rational(1, 1), 0));
    visited_from_start[1][1] = "";

    q.push(Node(target, 1));
    visited_from_target[target.p][target.q] = "";

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        if (current.direction == 0 && visited_from_target.find(current.val.p) != visited_from_target.end() && visited_from_target[current.val.p].find(current.val.q) != visited_from_target[current.val.p].end()) {
            string path_from_target = visited_from_target[current.val.p][current.val.q];
            reverse(path_from_target.begin(), path_from_target.end());
            return visited_from_start[current.val.p][current.val.q] + path_from_target;
        }
        if (current.direction == 1 && visited_from_start.find(current.val.p) != visited_from_start.end() && visited_from_start[current.val.p].find(current.val.q) != visited_from_start[current.val.p].end()) {
            string path_from_target = visited_from_target[current.val.p][current.val.q];
            reverse(path_from_target.begin(), path_from_target.end());
            return visited_from_start[current.val.p][current.val.q] + path_from_target;
        }

        // 向左走
        Rational left(current.val.p + current.val.q, current.val.q);
        if (current.direction == 0 && (visited_from_start.find(left.p) == visited_from_start.end() || visited_from_start[left.p].find(left.q) == visited_from_start[left.p].end())) {
            visited_from_start[left.p][left.q] = visited_from_start[current.val.p][current.val.q] + "L";
            q.push(Node(left, current.direction));
        }
        if (current.direction == 1 && (visited_from_target.find(left.p) == visited_from_target.end() || visited_from_target[left.p].find(left.q) == visited_from_target[left.p].end())) {
            visited_from_target[left.p][left.q] = "L" + visited_from_target[current.val.p][current.val.q];
            q.push(Node(left, current.direction));
        }

        // 向右走
        Rational right(current.val.p, current.val.p + current.val.q);
        if (current.direction == 0 && (visited_from_start.find(right.p) == visited_from_start.end() || visited_from_start[right.p].find(right.q) == visited_from_start[right.p].end())) {
            visited_from_start[right.p][right.q] = visited_from_start[current.val.p][current.val.q] + "R";
            q.push(Node(right, current.direction));
        }
        if (current.direction == 1 && (visited_from_target.find(right.p) == visited_from_target.end() || visited_from_target[right.p].find(right.q) == visited_from_target[right.p].end())) {
            visited_from_target[right.p][right.q] = "R" + visited_from_target[current.val.p][current.val.q];
            q.push(Node(right, current.direction));
        }
    }

    return "";
}

int main() {
    long long p, q;
    cin >> p >> q;

    Rational target(p, q);
    string path = bidirectional_bfs(target);

    cout << path << endl;

    return 0;
}