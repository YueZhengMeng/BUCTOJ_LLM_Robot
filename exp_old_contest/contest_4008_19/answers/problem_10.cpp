/* 
  Lumina‐T2X Unified Encoder
  - Image: 2D 4×4 block‐sum per channel + CLS  
  - Video: 3D 4×4×4 block‐sum per channel + CLS  
  - Audio: window into overlapping 40‐sample frames → pseudo‐images → video‐encoder  
  - Text: ASCII‐sum(word)+position → sentence‐sum → 32‐dim mod‐1557 vector 
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Process a "video" of dims (t,3,h,w) by 4×4×4 block sum → tokens + CLS
void encode_video(const vector<vector<vector<vector<int>>>> &vid) {
    int t = vid.size(), C = 3, h = vid[0][0].size(), w = vid[0][0][0].size();
    int tp = t / 4, hp = h / 4, wp = w / 4;
    // Prepare CLS = zero vector
    cout << 0 << ' ' << 0 << ' ' << 0 << "\n";
    // Block‐sum
    for(int bt = 0; bt < tp; bt++) {
        for(int bh = 0; bh < hp; bh++) {
            for(int bw = 0; bw < wp; bw++) {
                ll s0 = 0, s1 = 0, s2 = 0;
                for(int dt = 0; dt < 4; dt++)
                for(int di = 0; di < 4; di++)
                for(int dj = 0; dj < 4; dj++) {
                    int tt = bt*4 + dt;
                    int ii = bh*4 + di;
                    int jj = bw*4 + dj;
                    s0 += vid[tt][0][ii][jj];
                    s1 += vid[tt][1][ii][jj];
                    s2 += vid[tt][2][ii][jj];
                }
                cout << s0 << ' ' << s1 << ' ' << s2 << "\n";
            }
        }
    }
}

// Process an "image" of dims (3,h,w) as video with t=1 → only 2D blocks 4×4
void encode_image(const vector<vector<vector<int>>> &img) {
    int C = 3, h = img[0].size(), w = img[0][0].size();
    int hp = h/4, wp = w/4;
    cout << 0 << ' ' << 0 << ' ' << 0 << "\n";
    for(int bh = 0; bh < hp; bh++) {
        for(int bw = 0; bw < wp; bw++) {
            ll s0=0, s1=0, s2=0;
            for(int di = 0; di < 4; di++)
            for(int dj = 0; dj < 4; dj++) {
                int ii = bh*4 + di;
                int jj = bw*4 + dj;
                s0 += img[0][ii][jj];
                s1 += img[1][ii][jj];
                s2 += img[2][ii][jj];
            }
            cout << s0 << ' ' << s1 << ' ' << s2 << "\n";
        }
    }
}

// Text encoder
void encode_text(const string &s) {
    vector<vector<ll>> sentences;
    int n = s.size();
    ll curWord = 0; bool inWord = false;
    vector<ll> curSentence;
    // split into words & sentences
    for(int i = 0; i <= n; i++) {
        char c = (i<n? s[i] : '.'); // sentinel to flush last
        if (isalpha(c)) {
            inWord = true;
            curWord += (int)c;
        } else {
            if (inWord) {
                curSentence.push_back(curWord);
                curWord = 0;
                inWord = false;
            }
            if (c == ',' || c == ' ') {
                // skip
            } else if (c == '.') {
                if (!curSentence.empty()) {
                    sentences.push_back(curSentence);
                    curSentence.clear();
                }
            }
        }
    }
    // For each sentence, add position, sum, build 32‐dim
    for(auto &sent : sentences) {
        ll sVal = 0; 
        for(int i = 0; i < (int)sent.size(); i++) {
            sent[i] += (i+1);
            sVal += sent[i];
        }
        // 32 dims
        for(int i = 1; i <= 32; i++) {
            ll v = (sVal * i) % 1557;
            cout << v << (i<32? ' ' : '\n');
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int k; 
    if(!(cin >> k)) return 0;

    if(k == 0) {
        // Image
        int n, m; 
        cin >> n >> m;
        vector<vector<vector<int>>> img(3,
            vector<vector<int>>(n, vector<int>(m))
        );
        for(int c = 0; c < 3; c++)
            for(int i = 0; i < n; i++)
                for(int j = 0; j < m; j++)
                    cin >> img[c][i][j];
        encode_image(img);

    } else if (k == 1) {
        // Video
        int t, n, m; 
        cin >> t >> n >> m;
        vector<vector<vector<vector<int>>>> vid(
            t, vector<vector<vector<int>>>(3,
                vector<vector<int>>(n, vector<int>(m))));
        for(int tt = 0; tt < t; tt++)
         for(int c = 0; c < 3; c++)
          for(int i = 0; i < n; i++)
           for(int j = 0; j < m; j++)
            cin >> vid[tt][c][i][j];
        encode_video(vid);

    } else if (k == 2) {
        // Audio → pseudo‐video
        int N; 
        cin >> N;
        vector<int> a(N);
        for(int i = 0; i < N; i++) cin >> a[i];
        int T = N/20 - 1; // number of 40‐sample windows
        vector<vector<vector<vector<int>>>> vid(
            T, vector<vector<vector<int>>>(3,
                vector<vector<int>>(40, vector<int>(40))));
        for(int f = 0; f < T; f++){
            int st = f*20;
            for(int x = 0; x < 40; x++){
                int val = a[st + x]; // 0..40
                for(int row = 0; row < 40; row++){
                    // [FIX] 按题意：1-based 行号 > val → 0-based row >= val
                    int px = (row >= val ? 255 : 0);
                    for(int c = 0; c < 3; c++)
                        vid[f][c][row][x] = px;
                }
            }
        }
        encode_video(vid);

    } else if (k == 3) {
        // Text
        int n; 
        cin >> n;
        cin.get(); // consume newline
        string s;
        getline(cin, s);
        encode_text(s);
    }

    return 0;
}