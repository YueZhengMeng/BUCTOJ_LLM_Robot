/* 文件头注释：使用改进的缓存替换策略，最小化取书次数 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    // [FIX] 处理m=0的特殊情况
    if (m == 0) {
        cout << n << endl;
        return 0;
    }

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // 预计算每个漫画的所有出现位置
    unordered_map<int, vector<int>> comicPositions;
    for (int i = 0; i < n; ++i) {
        comicPositions[a[i]].push_back(i);
    }

    // 为每个漫画创建迭代器，用于快速查找下一次使用时间
    unordered_map<int, int> nextUseIndex;
    for (auto& pair : comicPositions) {
        nextUseIndex[pair.first] = 0;
    }

    // 使用优先队列维护缓存中漫画的下一次使用时间
    unordered_set<int> cacheSet; // 快速判断漫画是否在缓存中
    // 优先队列存储（下一次使用时间，漫画编号）
    priority_queue<pair<int, int>> cacheQueue;

    int count = 0; // 记录取书次数

    for (int i = 0; i < n; ++i) {
        int comic = a[i];
        if (cacheSet.find(comic) != cacheSet.end()) {
            // 如果漫画已经在缓存中，更新它的下一次使用时间
            int nextUseTime = n;
            if (nextUseIndex.at(comic) + 1 < comicPositions.at(comic).size()) {
                nextUseTime = comicPositions.at(comic)[nextUseIndex.at(comic) + 1];
            }
            cacheQueue.push({nextUseTime, comic});
            nextUseIndex.at(comic)++;
        } else {
            // 如果漫画不在缓存中，需要从书架上取
            count++;
            if (cacheSet.size() == m) {
                // 如果缓存已满，移除未来最久不会被使用的漫画
                while (!cacheQueue.empty()) {
                    auto top = cacheQueue.top();
                    if (cacheSet.find(top.second) == cacheSet.end() || 
                        top.first != comicPositions.at(top.second)[nextUseIndex.at(top.second)]) {
                        // 如果队列中的元素已经不在缓存中或者时间已经更新，则弹出
                        cacheQueue.pop();
                    } else {
                        break;
                    }
                }
                // [FIX] 确保优先队列不为空
                if (!cacheQueue.empty()) {
                    auto toRemove = cacheQueue.top();
                    cacheQueue.pop();
                    cacheSet.erase(toRemove.second);
                }
            }
            // 将新漫画添加到缓存中
            cacheSet.insert(comic);
            int nextUseTime = n;
            if (nextUseIndex.at(comic) + 1 < comicPositions.at(comic).size()) {
                nextUseTime = comicPositions.at(comic)[nextUseIndex.at(comic) + 1];
            }
            cacheQueue.push({nextUseTime, comic});
            nextUseIndex.at(comic)++;
        }
    }

    cout << count << endl;
    return 0;
}