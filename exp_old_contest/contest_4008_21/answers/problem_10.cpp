/* 文件头注释：文本数据编码为token */
#include <bits/stdc++.h>
#include <regex> // 引入正则表达式库
using namespace std;

// 函数：将单词转换为数值表示
int wordToValue(const string& word) {
    int value = 0;
    for (char ch : word) {
        value += ch;
    }
    return value;
}

// 函数：将句子转换为32维token
vector<int> sentenceToToken(int sentenceValue) {
    vector<int> token(32);
    for (int i = 0; i < 32; ++i) {
        token[i] = (sentenceValue * (i + 1)) % 1557;
    }
    return token;
}

int main() {
    int k;
    cin >> k;
    if (k == 3) {
        int n;
        cin >> n;
        cin.ignore(); // 忽略换行符
        string text;
        getline(cin, text);
        
        // 预处理：去除多余空格
        text.erase(unique(text.begin(), text.end(), [](char a, char b) {
            return a == ' ' && b == ' ';
        }), text.end());
        
        // 使用正则表达式分割句子
        regex sentenceRegex(R"([^\.]*\.?)");  // [FIX] 修改正则表达式以正确捕获包含句号的句子
        vector<string> sentences;
        for (sregex_iterator it(text.begin(), text.end(), sentenceRegex), end_it; it != end_it; ++it) {
            string sentence = it->str();
            // 去除句子两端的空格
            sentence.erase(0, sentence.find_first_not_of(' '));
            sentence.erase(sentence.find_last_not_of(' ') + 1);
            if (!sentence.empty()) {
                sentences.push_back(sentence);
            }
        }
        
        // 处理每个句子
        for (const string& sentence : sentences) {
            // 使用正则表达式分割单词
            regex wordRegex(R"([^ ,]+)");  // [FIX] 保留原单词分割正则表达式
            vector<string> words;
            for (sregex_iterator it(sentence.begin(), sentence.end(), wordRegex), end_it; it != end_it; ++it) {
                string word = it->str();
                if (!word.empty()) {
                    words.push_back(word);
                }
            }
            
            // 计算句子value
            int sentenceValue = 0;
            for (size_t i = 0; i < words.size(); ++i) {
                int wordValue = wordToValue(words[i]);
                sentenceValue += wordValue + (i + 1); // 加上位置编码
            }
            
            // 生成32维token
            vector<int> token = sentenceToToken(sentenceValue);
            for (int val : token) {
                cout << val << " ";
            }
            cout << endl;
        }
    }
    return 0;
}