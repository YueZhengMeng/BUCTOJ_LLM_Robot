#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

// A value larger than any possible chapter index n, representing "never used again" or "used very far in the future".
const int INF_NXT_USE = 200005; 

// Function to find the next occurrence of manga_id strictly after current_idx
// n_chapters is the total number of chapters (used for upper_bound logic, not strictly as INF here)
int find_next_occurrence(int manga_id, int current_idx, int n_chapters, const std::vector<std::vector<int>>& all_occurrences) {
    // Check if manga_id is valid and has any occurrences recorded
    if (manga_id >= all_occurrences.size() || all_occurrences[manga_id].empty()) {
        return INF_NXT_USE;
    }
    const auto& occurrences_list = all_occurrences[manga_id];
    // Find the first occurrence strictly greater than current_idx
    auto it = std::upper_bound(occurrences_list.begin(), occurrences_list.end(), current_idx);
    
    if (it == occurrences_list.end()) {
        // No future occurrence found
        return INF_NXT_USE;
    }
    return *it; // Return the index of the next occurrence
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m; // n: chapters, m: desk capacity
    std::cin >> n >> m;

    std::vector<int> a(n); // Manga needed for each chapter
    int max_manga_id = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        if (a[i] > max_manga_id) {
            max_manga_id = a[i];
        }
    }

    // Precompute all occurrences of each manga
    std::vector<std::vector<int>> all_occurrences(max_manga_id + 1);
    for (int i = 0; i < n; ++i) {
        all_occurrences[a[i]].push_back(i);
    }

    int fetch_count = 0;
    // desk_pq stores {-next_future_use_idx, manga_id}
    // Using negative next_future_use_idx allows std::set (min-heap) to find the item
    // with the largest next_future_use_idx (i.e., smallest -next_future_use_idx)
    std::set<std::pair<int, int>> desk_pq; 
    // Stores manga_ids currently on the desk for O(1) average presence check
    std::unordered_set<int> mangas_on_desk_set; 
    // Maps manga_id to its current {-next_future_use_idx} value in desk_pq for efficient removal/update
    std::unordered_map<int, int> manga_to_neg_next_use_idx; 

    for (int i = 0; i < n; ++i) { // Iterate through chapters
        int current_manga = a[i];

        if (mangas_on_desk_set.count(current_manga)) {
            // Hit: manga is already on desk. Update its priority in desk_pq.
            int old_neg_next_use = manga_to_neg_next_use_idx[current_manga];
            desk_pq.erase({old_neg_next_use, current_manga});

            int new_next_use = find_next_occurrence(current_manga, i, n, all_occurrences);
            
            desk_pq.insert({-new_next_use, current_manga});
            manga_to_neg_next_use_idx[current_manga] = -new_next_use;
        } else {
            // Miss: manga is not on desk.
            fetch_count++;

            if (mangas_on_desk_set.size() == m) {
                // Desk is full. Evict the manga whose next use is furthest in the future.
                // This is the first element in desk_pq due to the negative indexing.
                std::pair<int, int> item_to_evict_pair = *desk_pq.begin();
                int manga_to_evict = item_to_evict_pair.second;

                desk_pq.erase(desk_pq.begin());
                mangas_on_desk_set.erase(manga_to_evict);
                manga_to_neg_next_use_idx.erase(manga_to_evict);
            }

            // Add current_manga to the desk.
            int next_use = find_next_occurrence(current_manga, i, n, all_occurrences);

            mangas_on_desk_set.insert(current_manga);
            desk_pq.insert({-next_use, current_manga});
            manga_to_neg_next_use_idx[current_manga] = -next_use;
        }
    }

    std::cout << fetch_count << std::endl;

    return 0;
}