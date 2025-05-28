#include <iostream>
#include <vector>
#include <string>
#include <numeric> // For std::accumulate (not directly used but good for sums)
#include <cctype>  // For std::isalpha

// Helper function to print a token (vector of ints)
void print_int_token(const std::vector<int>& token) {
    for (size_t i = 0; i < token.size(); ++i) {
        std::cout << token[i] << (i == token.size() - 1 ? "" : " ");
    }
    std::cout << std::endl;
}

// Helper function to print a token (vector of long longs)
void print_long_long_token(const std::vector<long long>& token) {
    for (size_t i = 0; i < token.size(); ++i) {
        std::cout << token[i] << (i == token.size() - 1 ? "" : " ");
    }
    std::cout << std::endl;
}

void solve_image() {
    int n, m;
    std::cin >> n >> m;
    // image_data[channel][height][width]
    std::vector<std::vector<std::vector<int>>> image_data(3, std::vector<std::vector<int>>(n, std::vector<int>(m)));
    for (int c = 0; c < 3; ++c) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                std::cin >> image_data[c][i][j];
            }
        }
    }

    int n_new = n / 4;
    int m_new = m / 4;

    std::vector<std::vector<int>> output_tokens;
    output_tokens.push_back({0, 0, 0}); // CLS token

    // convolved_channels_data[channel][new_height][new_width]
    std::vector<std::vector<std::vector<int>>> convolved_channels_data(3, std::vector<std::vector<int>>(n_new, std::vector<int>(m_new)));

    for (int c = 0; c < 3; ++c) {
        for (int ni = 0; ni < n_new; ++ni) {
            for (int mi = 0; mi < m_new; ++mi) {
                int sum_val = 0;
                for (int r_offset = 0; r_offset < 4; ++r_offset) {
                    for (int col_offset = 0; col_offset < 4; ++col_offset) {
                        sum_val += image_data[c][ni * 4 + r_offset][mi * 4 + col_offset];
                    }
                }
                convolved_channels_data[c][ni][mi] = sum_val;
            }
        }
    }

    // Assemble tokens: iterate through spatial patches, get value from each channel
    for (int ni = 0; ni < n_new; ++ni) {
        for (int mi = 0; mi < m_new; ++mi) {
            std::vector<int> patch_token(3);
            patch_token[0] = convolved_channels_data[0][ni][mi];
            patch_token[1] = convolved_channels_data[1][ni][mi];
            patch_token[2] = convolved_channels_data[2][ni][mi];
            output_tokens.push_back(patch_token);
        }
    }
    
    for (const auto& token : output_tokens) {
        print_int_token(token);
    }
}

void solve_video() {
    int t, n, m;
    std::cin >> t >> n >> m;
    // video_data[time][channel][height][width]
    std::vector<std::vector<std::vector<std::vector<int>>>> video_data(
        t, std::vector<std::vector<std::vector<int>>>(
               3, std::vector<std::vector<int>>(
                      n, std::vector<int>(m))));

    for (int ti = 0; ti < t; ++ti) {
        for (int c = 0; c < 3; ++c) {
            for (int r = 0; r < n; ++r) {
                for (int col = 0; col < m; ++col) {
                    std::cin >> video_data[ti][c][r][col];
                }
            }
        }
    }

    int t_new = t / 4;
    int n_new = n / 4;
    int m_new = m / 4;

    // convolved_video_data[new_time][channel][new_height][new_width]
    std::vector<std::vector<std::vector<std::vector<int>>>> convolved_video_data(
        t_new, std::vector<std::vector<std::vector<int>>>(
                   3, std::vector<std::vector<int>>(
                          n_new, std::vector<int>(m_new))));

    for (int ti_new = 0; ti_new < t_new; ++ti_new) {
        for (int c = 0; c < 3; ++c) {
            for (int ni_new = 0; ni_new < n_new; ++ni_new) {
                for (int mi_new = 0; mi_new < m_new; ++mi_new) {
                    int current_sum = 0; 
                    for (int dt = 0; dt < 4; ++dt) {
                        for (int dn = 0; dn < 4; ++dn) {
                            for (int dm = 0; dm < 4; ++dm) {
                                current_sum += video_data[ti_new * 4 + dt][c][ni_new * 4 + dn][mi_new * 4 + dm];
                            }
                        }
                    }
                    convolved_video_data[ti_new][c][ni_new][mi_new] = current_sum;
                }
            }
        }
    }
    
    std::vector<std::vector<int>> output_tokens;
    output_tokens.push_back({0, 0, 0}); // CLS token

    // Assemble tokens: iterate new_time, new_height, new_width
    for (int ti_new = 0; ti_new < t_new; ++ti_new) {
        for (int ni_new = 0; ni_new < n_new; ++ni_new) {
            for (int mi_new = 0; mi_new < m_new; ++mi_new) {
                std::vector<int> current_patch_token(3);
                current_patch_token[0] = convolved_video_data[ti_new][0][ni_new][mi_new];
                current_patch_token[1] = convolved_video_data[ti_new][1][ni_new][mi_new];
                current_patch_token[2] = convolved_video_data[ti_new][2][ni_new][mi_new];
                output_tokens.push_back(current_patch_token);
            }
        }
    }

    for (const auto& token : output_tokens) {
        print_int_token(token);
    }
}


void solve_audio() {
    int l_audio;
    std::cin >> l_audio;
    std::vector<int> audio_data(l_audio);
    for (int i = 0; i < l_audio; ++i) {
        std::cin >> audio_data[i];
    }

    int frame_len = 40; // Each segment is 40 samples long
    int frame_h = 40;   // Resulting image height
    int frame_w = 40;   // Resulting image width (since each sample is a column)
    int stride = 20;    // 50% overlap for 40-sample segments

    int t_audio = (l_audio - frame_len) / stride + 1; // Number of frames

    // pseudo_video_data[t_audio][channel][height][width]
    std::vector<std::vector<std::vector<std::vector<int>>>> pseudo_video_data(
        t_audio, std::vector<std::vector<std::vector<int>>>(
                     3, std::vector<std::vector<int>>(
                            frame_h, std::vector<int>(frame_w))));

    for (int ti = 0; ti < t_audio; ++ti) {
        int segment_start_idx = ti * stride;
        for (int c = 0; c < 3; ++c) { // All 3 channels are the same
            for (int w_idx = 0; w_idx < frame_w; ++w_idx) { // w_idx is column, corresponds to audio sample in segment
                int audio_val_x = audio_data[segment_start_idx + w_idx];
                for (int h_idx = 0; h_idx < frame_h; ++h_idx) { // h_idx is row
                    // Rule: "在高度(行)维度，大于x的部分为全白（3通道均为255），小于等于x的部分为全黑（3通道均为0）"
                    // h_idx (0 to 39), audio_val_x (0 to 40)
                    if (h_idx <= audio_val_x) {
                        pseudo_video_data[ti][c][h_idx][w_idx] = 0;   // Black
                    } else {
                        pseudo_video_data[ti][c][h_idx][w_idx] = 255; // White
                    }
                }
            }
        }
    }

    // Now pseudo_video_data is [t_audio, 3, 40, 40]
    // Apply video encoding steps (same as solve_video, but with pseudo_video_data)
    int t_eff = t_audio / 4;
    int n_eff = frame_h / 4; // 40/4 = 10
    int m_eff = frame_w / 4; // 40/4 = 10

    // convolved_audio_frames[new_time][channel][new_height][new_width]
    std::vector<std::vector<std::vector<std::vector<int>>>> convolved_audio_frames(
        t_eff, std::vector<std::vector<std::vector<int>>>(
                   3, std::vector<std::vector<int>>(
                          n_eff, std::vector<int>(m_eff))));
    
    for (int ti_new = 0; ti_new < t_eff; ++ti_new) {
        for (int c = 0; c < 3; ++c) {
            for (int ni_new = 0; ni_new < n_eff; ++ni_new) {
                for (int mi_new = 0; mi_new < m_eff; ++mi_new) {
                    int current_sum = 0;
                    for (int dt = 0; dt < 4; ++dt) {
                        for (int dn = 0; dn < 4; ++dn) {
                            for (int dm = 0; dm < 4; ++dm) {
                                current_sum += pseudo_video_data[ti_new * 4 + dt][c][ni_new * 4 + dn][mi_new * 4 + dm];
                            }
                        }
                    }
                    convolved_audio_frames[ti_new][c][ni_new][mi_new] = current_sum;
                }
            }
        }
    }

    std::vector<std::vector<int>> output_tokens;
    output_tokens.push_back({0, 0, 0}); // CLS token

    for (int ti_new = 0; ti_new < t_eff; ++ti_new) {
        for (int ni_new = 0; ni_new < n_eff; ++ni_new) {
            for (int mi_new = 0; mi_new < m_eff; ++mi_new) {
                std::vector<int> current_patch_token(3);
                current_patch_token[0] = convolved_audio_frames[ti_new][0][ni_new][mi_new];
                current_patch_token[1] = convolved_audio_frames[ti_new][1][ni_new][mi_new];
                current_patch_token[2] = convolved_audio_frames[ti_new][2][ni_new][mi_new];
                output_tokens.push_back(current_patch_token);
            }
        }
    }
    
    for (const auto& token : output_tokens) {
        print_int_token(token);
    }
}

void solve_text() {
    int n_chars;
    std::cin >> n_chars;
    std::string text_content;
    text_content.resize(n_chars);
    // Read exactly n_chars, std::cin >> char handles whitespace correctly one by one.
    for (int i = 0; i < n_chars; ++i) {
        std::cin >> text_content[i]; 
    }

    std::string current_word_str;
    std::vector<long long> current_sentence_positional_values;
    int word_idx_in_sentence = 1;

    for (int i = 0; i < n_chars; ++i) {
        char ch = text_content[i];
        if (std::isalpha(ch)) {
            current_word_str += ch;
        } else { // Separator: ' ', ',', '.'
            if (!current_word_str.empty()) {
                long long ascii_sum = 0;
                for (char wc : current_word_str) {
                    ascii_sum += static_cast<long long>(wc);
                }
                current_sentence_positional_values.push_back(ascii_sum + word_idx_in_sentence);
                word_idx_in_sentence++;
                current_word_str.clear();
            }

            if (ch == '.') { // End of sentence
                if (!current_sentence_positional_values.empty()) {
                    long long sentence_value = 0;
                    for (long long val : current_sentence_positional_values) {
                        sentence_value += val;
                    }

                    std::vector<long long> sentence_tokens_32dim;
                    for (int k = 1; k <= 32; ++k) {
                        sentence_tokens_32dim.push_back((sentence_value * k) % 1557);
                    }
                    print_long_long_token(sentence_tokens_32dim);
                }
                current_sentence_positional_values.clear();
                word_idx_in_sentence = 1; // Reset for next sentence
            }
        }
    }
    // Per problem description and sample, last sentence is also terminated by '.'
    // If current_word_str is not empty and loop ends (e.g. text not ending with '.'),
    // it might need handling. But problem implies '.' termination for all sentences.
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int k_mode;
    std::cin >> k_mode;

    if (k_mode == 0) {
        solve_image();
    } else if (k_mode == 1) {
        solve_video();
    } else if (k_mode == 2) {
        solve_audio();
    } else if (k_mode == 3) {
        solve_text();
    }

    return 0;
}