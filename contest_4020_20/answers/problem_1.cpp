#include <iostream>
#include <vector>
#include <list>
#include <numeric>
#include <algorithm>

// Function to check if the current arrangement of cards is sorted (1, 2, ..., n)
bool check_if_sorted(const std::vector<int>& cards, int n) {
    // cards.size() should always be n in this problem's context after initialization
    if (static_cast<int>(cards.size()) != n) return false; 
    for (int i = 0; i < n; ++i) {
        if (cards[i] != i + 1) {
            return false;
        }
    }
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<int> p(n); // current permutation
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i];
    }

    if (check_if_sorted(p, n)) {
        std::cout << 0 << std::endl;
        return 0;
    }

    int rounds = 0;
    while(true) {
        rounds++;

        std::list<int> active_deck;
        for(int card_val : p) {
            active_deck.push_back(card_val);
        }
        
        std::vector<int> next_p;
        next_p.reserve(n); // Pre-allocate memory for efficiency

        for (int k = 0; k < n; ++k) { // Deal n cards
            if (active_deck.size() == 1) {
                int dealt_card = active_deck.front();
                active_deck.pop_front();
                next_p.push_back(dealt_card);
            } else { // active_deck.size() >= 2
                int card1 = active_deck.front();
                
                // Get iterator to the second element. std::next is C++11.
                // Alternatively, auto it_card2 = active_deck.begin(); ++it_card2;
                auto it_card2 = std::next(active_deck.begin()); 
                int card2 = *it_card2;

                if (card1 < card2) {
                    int dealt_card = card1;
                    active_deck.pop_front(); // Remove first element
                    next_p.push_back(dealt_card);
                } else { 
                    // Since cards are distinct and not (card1 < card2), it must be card2 < card1
                    int dealt_card = card2;
                    active_deck.erase(it_card2); // Remove second element
                    next_p.push_back(dealt_card);
                }
            }
        }
        
        p = next_p; // Update p for the next round using vector assignment

        if (check_if_sorted(p, n)) {
            break;
        }
    }

    std::cout << rounds << std::endl;

    return 0;
}