#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

// Structure to hold item properties
struct Item {
    int id; // Original index
    int a, b; // Values from arrays a and b
    int diff; // Difference a - b
};

// Comparator for sorting items by diff (a_i - b_i) in descending order.
// Tie-breaking by original id (smaller id first) for consistency.
bool compareItemsByDiff(const Item& item1, const Item& item2) {
    if (item1.diff != item2.diff) {
        return item1.diff > item2.diff;
    }
    return item1.id < item2.id;
}

// Comparator for sorting items by b_value in ascending order.
// Used for identifying B-candidates to discard (those with smallest b_values).
// Tie-breaking by original id.
bool compareItemsByB(const Item& item1, const Item& item2) {
    if (item1.b != item2.b) {
        return item1.b < item2.b;
    }
    return item1.id < item2.id;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, s_count, t_count;
    std::cin >> n >> s_count >> t_count;

    std::vector<Item> items(n);
    std::vector<int> temp_a_vals(n);
    std::vector<int> temp_b_vals(n); 

    for (int i = 0; i < n; ++i) {
        std::cin >> temp_a_vals[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> temp_b_vals[i];
    }

    // Populate the Item structures
    for (int i = 0; i < n; ++i) {
        items[i].id = i;
        items[i].a = temp_a_vals[i];
        items[i].b = temp_b_vals[i];
        items[i].diff = items[i].a - items[i].b;
    }

    long long total_score = 0;

    // Step 1: Initialize total_score.
    // Assume all n items are initially chosen for group B, contributing b_i.
    for (int i = 0; i < n; ++i) {
        total_score += items[i].b;
    }

    // Step 2: Sort all items by their difference (a_i - b_i) in descending order.
    std::sort(items.begin(), items.end(), compareItemsByDiff);

    // Step 3: Select s_count items for group A.
    // These are the first s_count items in the diff-sorted list.
    // For each, change its contribution from b_i to a_i by adding (a_i - b_i).
    for (int i = 0; i < s_count; ++i) {
        total_score += items[i].diff; 
    }
    // At this point, total_score reflects:
    // - items[0]...items[s_count-1] (from sorted list) contribute their a_value.
    // - items[s_count]...items[n-1] (from sorted list) contribute their b_value.

    // Step 4: Handle selections for group B and discards.
    // Items currently considered for group B are items[s_count] through items[n-1]
    // from the diff-sorted list. There are (n - s_count) such items.
    // We need to select t_count items for group B from this pool.
    // Thus, we must discard (n - s_count) - t_count items from this pool.
    // These are the ones with the smallest b_values.
    
    std::vector<Item> b_selection_candidates;
    for (int i = s_count; i < n; ++i) {
        // items[i] here refers to an item from the original list,
        // but it's the i-th item in the diff-sorted sequence.
        b_selection_candidates.push_back(items[i]);
    }

    // Sort these B-candidates by their b_value in ascending order.
    std::sort(b_selection_candidates.begin(), b_selection_candidates.end(), compareItemsByB);

    int num_items_in_b_pool = n - s_count; 
    int num_to_discard_from_b_pool = num_items_in_b_pool - t_count;
    
    for (int i = 0; i < num_to_discard_from_b_pool; ++i) {
        // b_selection_candidates[i] is one of the items with the smallest b_values
        // among those not chosen for A.
        // This item was initially counted with its b_value. Now, it's discarded.
        total_score -= b_selection_candidates[i].b;
    }

    std::cout << total_score << std::endl;

    return 0;
}