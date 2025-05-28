#include <iostream>
#include <vector>
#include <string> // Not strictly needed for this problem logic but often useful.

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    std::cin >> n >> m;

    int h_patches = n / 4;
    int w_patches = m / 4;
    int num_image_tokens = h_patches * w_patches;

    // Store image data: image_data[channel][row][col]
    std::vector<std::vector<std::vector<int>>> image_data(
        3, std::vector<std::vector<int>>(n, std::vector<int>(m)));

    // Read input for 3 channels
    for (int c = 0; c < 3; ++c) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                std::cin >> image_data[c][i][j];
            }
        }
        // Note: cin >> int skips whitespace, including blank lines between matrices.
    }

    // Stores the final (num_image_tokens + 1) x 3 matrix
    std::vector<std::vector<int>> transformed_tokens(
        num_image_tokens + 1, std::vector<int>(3));

    // Process each patch to form image tokens
    for (int token_idx = 0; token_idx < num_image_tokens; ++token_idx) {
        // Determine which patch this token_idx corresponds to (row-major order of patches)
        int patch_grid_row = token_idx / w_patches;
        int patch_grid_col = token_idx % w_patches;

        // Determine the top-left corner of this patch in the original image
        int start_img_row = patch_grid_row * 4;
        int start_img_col = patch_grid_col * 4;

        // Calculate sum for this patch for each channel
        for (int c = 0; c < 3; ++c) { // 0:R, 1:G, 2:B
            int current_patch_sum = 0;
            for (int r_offset = 0; r_offset < 4; ++r_offset) {
                for (int c_offset = 0; c_offset < 4; ++c_offset) {
                    current_patch_sum += image_data[c][start_img_row + r_offset][start_img_col + c_offset];
                }
            }
            transformed_tokens[token_idx][c] = current_patch_sum;
        }
    }

    // Add the CLS token
    transformed_tokens[num_image_tokens][0] = static_cast<int>('l');
    transformed_tokens[num_image_tokens][1] = static_cast<int>('x');
    transformed_tokens[num_image_tokens][2] = static_cast<int>('r');

    // Output the resulting matrix
    for (int i = 0; i < num_image_tokens + 1; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << transformed_tokens[i][j] << (j == 2 ? "" : " ");
        }
        std::cout << std::endl;
    }

    return 0;
}