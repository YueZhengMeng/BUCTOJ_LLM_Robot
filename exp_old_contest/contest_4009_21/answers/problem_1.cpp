/* 文件头注释：统计电影名称出现频率，找出出现次数最多的电影名称 */
#include <bits/stdc++.h>
#include <regex> // [FIX] 引入正则表达式库
using namespace std;

int main() {
    // 定义所有电影名称
    vector<string> movies = {
        "Gone with the Wind", "Twelve Angry Men", "The Sound of Music",
        "The Godfather", "Star Wars", "Alien", "Back to the Future"
    };

    // 将电影名称转换为小写，方便统计
    for (string& movie : movies) {
        transform(movie.begin(), movie.end(), movie.begin(), ::tolower);
    }

    // 定义哈希表，用于统计每个电影名称的出现次数
    unordered_map<string, int> frequency;

    // 模拟诗的内容
    string poem = R"(
        In days of old when knights were bold,
        And journeys gone with the wind,
        A tale was told of men so cold,
        Twelve angry men within.

        Their fury raged like fire ablaze,
        But hark! What's that I hear?
        The sound of music through the haze,
        A melody so clear.

        It spoke of love and family ties,
        Of the godfather's might,
        And battles fought in distant skies,
        In star wars day and night.

        But though the future seemed so grand,
        With alien life to find,
        Our hero wished to take a stand,
        And journey back to the future in time.

        For in his heart he knew so true,
        That the sound of music's call,
        Would guide him home to love anew,
        And peace would come to all.
    )";

    // 将诗的内容转换为小写
    transform(poem.begin(), poem.end(), poem.begin(), ::tolower);

    // 统计每个电影名称在诗中的出现次数
    for (const string& movie : movies) {
        // [FIX] 使用正则表达式进行匹配，忽略标点符号和空白字符，并确保不区分大小写
        regex pattern("\\b" + movie + "\\b", regex_constants::icase);
        auto words_begin = sregex_iterator(poem.begin(), poem.end(), pattern);
        auto words_end = sregex_iterator();
        frequency[movie] = distance(words_begin, words_end);
    }

    // 找出出现次数最多的电影名称
    string favorite_movie;
    int max_count = 0;
    for (const auto& pair : frequency) {
        if (pair.second > max_count) {
            max_count = pair.second;
            favorite_movie = pair.first;
        }
    }

    // 输出结果
    cout << favorite_movie << endl;

    return 0;
}