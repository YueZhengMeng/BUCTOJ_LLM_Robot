/* 文件头注释：模拟瑞士轮赛制，计算最多能有多少弱队进入八强 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int x;
    cin >> x;
    
    // 强队和弱队的数量
    int strong = 16 - x;
    int weak = x;
    
    // 模拟瑞士轮赛制
    // 每轮比赛后，记录每支队伍的战绩
    // 0: 未比赛, 1: 1胜, 2: 2胜, 3: 3胜 (晋级)
    // -1: 1负, -2: 2负, -3: 3负 (淘汰)
    
    // 初始化所有队伍的战绩为0
    vector<int> records(16, 0);
    
    // 第一轮：强队对弱队，强队必胜
    for (int i = 0; i < strong; ++i) {
        records[i] = 1; // 强队1胜
    }
    for (int i = strong; i < 16; ++i) {
        records[i] = -1; // 弱队1负
    }
    
    // 第二轮：1-0组互相对抗，0-1组互相对抗
    // 强队之间随机对战，弱队之间确保尽可能多的弱队获得胜利
    // 强队之间对战，随机一半胜，一半负
    for (int i = 0; i < strong; i += 2) {
        records[i] = 2; // 强队2胜
        records[i+1] = 0; // 强队1胜1负
    }
    // 弱队之间对战，确保只有一半的弱队获得胜利
    for (int i = strong; i < 16; i += 2) {
        if (i + 1 < 16) {
            records[i] = 0; // 弱队1胜1负
            records[i+1] = -2; // 弱队2负
        }
    }
    
    // 第三轮：2-0组进行BO3，0-2组进行BO3，1-1组继续BO1
    // 2-0组：强队之间对战，随机一半胜，一半负
    for (int i = 0; i < strong; i += 2) {
        if (records[i] == 2) {
            records[i] = 3; // 强队3胜，晋级
            records[i+1] = 1; // 强队2胜1负
        }
    }
    // 0-2组：弱队之间对战，确保只有部分弱队获得胜利
    for (int i = strong; i < 16; i += 2) {
        if (records[i] == -2 && i + 1 < 16) {
            records[i] = -1; // 弱队1胜2负
            records[i+1] = -3; // 弱队3负，淘汰
        }
    }
    // 1-1组：弱队之间对战，确保只有部分弱队获得胜利
    for (int i = strong; i < 16; i += 2) {
        if (records[i] == 0 && i + 1 < 16) {
            records[i] = 1; // 弱队2胜1负
            records[i+1] = -1; // 弱队1胜2负
        }
    }
    
    // 第四轮：2-1组进行BO3，1-2组进行BO3
    // 2-1组：强队之间对战，随机一半胜，一半负
    for (int i = 0; i < strong; i += 2) {
        if (records[i] == 1) {
            records[i] = 2; // 强队3胜1负
            records[i+1] = 1; // 强队2胜2负
        }
    }
    // 1-2组：弱队之间对战，确保只有部分弱队获得胜利
    for (int i = strong; i < 16; i += 2) {
        if (records[i] == -1 && i + 1 < 16) {
            records[i] = 0; // 弱队2胜2负
            records[i+1] = -2; // 弱队1胜3负，淘汰
        }
    }
    
    // 第五轮：2-2组进行BO3
    // 2-2组：弱队之间对战，确保只有3支弱队能够晋级
    int weak_advance = 0;
    for (int i = strong; i < 16; i += 2) {
        if (records[i] == 0 && i + 1 < 16) {
            if (weak_advance < 3) {
                records[i] = 1; // 弱队3胜2负，晋级
                weak_advance++;
            } else {
                records[i] = -1; // 弱队2胜3负，淘汰
            }
            records[i+1] = -1; // 弱队2胜3负，淘汰
        }
    }
    
    // 统计晋级的弱队数量
    weak_advance = 0;
    for (int i = strong; i < 16; ++i) {
        if (records[i] >= 1) {
            weak_advance++;
        }
    }
    
    cout << weak_advance << endl;
    
    return 0;
}