/* 文件头注释：使用归并排序合并两个有序链表 */
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int id;
    int score;
    Node* next;
    Node(int id, int score) : id(id), score(score), next(nullptr) {}
};

// 合并两个有序链表
Node* mergeLists(Node* a, Node* b) {
    Node dummy(0, 0);
    Node* tail = &dummy;

    while (a && b) {
        if (a->id < b->id) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }

    if (a) tail->next = a;
    if (b) tail->next = b;

    return dummy.next;
}

// 打印链表
void printList(Node* head) {
    while (head) {
        cout << head->id << " " << head->score << endl;
        head = head->next;
    }
}

int main() {
    int N, M;
    cin >> N >> M;

    Node* a = nullptr;
    Node* b = nullptr;
    Node* tailA = nullptr;
    Node* tailB = nullptr;

    // 读取链表a
    for (int i = 0; i < N; ++i) {
        int id, score;
        cin >> id >> score;
        Node* newNode = new Node(id, score);
        if (!a) {
            a = newNode;
            tailA = a;
        } else {
            tailA->next = newNode;
            tailA = newNode;
        }
    }

    // 读取链表b
    for (int i = 0; i < M; ++i) {
        int id, score;
        cin >> id >> score;
        Node* newNode = new Node(id, score);
        if (!b) {
            b = newNode;
            tailB = b;
        } else {
            tailB->next = newNode;
            tailB = newNode;
        }
    }

    // 合并链表
    Node* mergedList = mergeLists(a, b);

    // 打印合并后的链表
    printList(mergedList);

    // 释放内存
    while (mergedList) {
        Node* temp = mergedList;
        mergedList = mergedList->next;
        delete temp;
    }

    return 0;
}