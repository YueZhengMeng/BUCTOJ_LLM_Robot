#include <iostream>
#include <vector>
#include <numeric>   // For std::accumulate (not used here, but common)
#include <algorithm> // For std::vector::assign

// Helper function to process matches in a pool
// nw_pool: number of Weak teams in the current score group
// ns_pool: number of Strong teams in the current score group
// References for results:
// w_wins_match: Weak teams from this pool that win their match
// w_loses_match: Weak teams from this pool that lose their match
// s_wins_match: Strong teams from this pool that win their match
// s_loses_match: Strong teams from this pool that lose their match
void process_matches_in_pool(int nw_pool, int ns_pool,
                             int& w_wins_match, int& w_loses_match,
                             int& s_wins_match, int& s_loses_match) {
    w_wins_match = 0; w_loses_match = 0;
    s_wins_match = 0; s_loses_match = 0;

    // Pair W vs W to maximize weak team wins
    int ww_pairs = nw_pool / 2;
    w_wins_match += ww_pairs;  // These weak teams win
    w_loses_match += ww_pairs; // These weak teams lose
    int remaining_w = nw_pool % 2;

    // Pair S vs S
    int ss_pairs = ns_pool / 2;
    s_wins_match += ss_pairs;  // These strong teams win
    s_loses_match += ss_pairs; // These strong teams lose
    int remaining_s = ns_pool % 2;

    // Pair remaining W vs S (if one of each remains)
    // This occurs if remaining_w == 1 (which implies remaining_s == 1,
    // as the total number of teams in a match group is even, so nw_pool and
    // ns_pool must have the same parity).
    if (remaining_w == 1) { 
        w_loses_match += 1; // Weak team plays Strong team and loses
        s_wins_match += 1;  // Strong team plays Weak team and wins
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int x; // Number of weak teams
    std::cin >> x;

    // w_st[i][j] = number of weak teams with i wins and j losses
    // s_st[i][j] = number of strong teams with i wins and j losses
    // Max wins/losses before qualification/elimination is 2 for teams still in play.
    // Using 4x4 arrays for indices 0..3 (wins/losses).
    std::vector<std::vector<int>> w_st(4, std::vector<int>(4, 0));
    std::vector<std::vector<int>> s_st(4, std::vector<int>(4, 0));
    
    int qualified_weak_teams = 0;
    // int eliminated_weak_teams = 0; // Can be tracked if needed

    // Initial state: All teams are 0 wins, 0 losses
    w_st[0][0] = x;
    s_st[0][0] = 16 - x;

    // Temporary state for building the next round's distribution
    std::vector<std::vector<int>> next_w_st(4, std::vector<int>(4, 0));
    std::vector<std::vector<int>> next_s_st(4, std::vector<int>(4, 0));
    
    int w_match_w, w_match_l, s_match_w, s_match_l; // For results from process_matches_in_pool

    // --- Round 1 ---
    // All teams are (0,0). Winners go to (1,0), Losers to (0,1).
    if (w_st[0][0] + s_st[0][0] > 0) {
        process_matches_in_pool(w_st[0][0], s_st[0][0], w_match_w, w_match_l, s_match_w, s_match_l);
        next_w_st[1][0] += w_match_w;
        next_w_st[0][1] += w_match_l;
        next_s_st[1][0] += s_match_w;
        next_s_st[0][1] += s_match_l;
    }
    w_st = next_w_st;
    s_st = next_s_st;
    next_w_st.assign(4, std::vector<int>(4, 0)); 
    next_s_st.assign(4, std::vector<int>(4, 0)); 

    // --- Round 2 ---
    // Pool (1,0) plays: Winners (2,0), Losers (1,1)
    if (w_st[1][0] + s_st[1][0] > 0) {
        process_matches_in_pool(w_st[1][0], s_st[1][0], w_match_w, w_match_l, s_match_w, s_match_l);
        next_w_st[2][0] += w_match_w;
        next_w_st[1][1] += w_match_l;
        next_s_st[2][0] += s_match_w;
        next_s_st[1][1] += s_match_l;
    }
    // Pool (0,1) plays: Winners (1,1), Losers (0,2)
    if (w_st[0][1] + s_st[0][1] > 0) {
        process_matches_in_pool(w_st[0][1], s_st[0][1], w_match_w, w_match_l, s_match_w, s_match_l);
        next_w_st[1][1] += w_match_w; 
        next_w_st[0][2] += w_match_l;
        next_s_st[1][1] += s_match_w; 
        next_s_st[0][2] += s_match_l;
    }
    w_st = next_w_st;
    s_st = next_s_st;
    next_w_st.assign(4, std::vector<int>(4, 0));
    next_s_st.assign(4, std::vector<int>(4, 0));
    
    // --- Round 3 ---
    // Pool (2,0) plays: Winners (3,0) qualify, Losers (2,1)
    if (w_st[2][0] + s_st[2][0] > 0) {
        process_matches_in_pool(w_st[2][0], s_st[2][0], w_match_w, w_match_l, s_match_w, s_match_l);
        qualified_weak_teams += w_match_w;
        next_w_st[2][1] += w_match_l;
        // next_s_st[2][1] would get s_match_l; s_match_w would qualify.
        next_s_st[2][1] += s_match_l;
    }
    // Pool (0,2) plays: Winners (1,2), Losers (0,3) eliminated
    if (w_st[0][2] + s_st[0][2] > 0) {
        process_matches_in_pool(w_st[0][2], s_st[0][2], w_match_w, w_match_l, s_match_w, s_match_l);
        next_w_st[1][2] += w_match_w;
        // eliminated_weak_teams += w_match_l;
        // next_s_st[1][2] would get s_match_w; s_match_l would be eliminated.
        next_s_st[1][2] += s_match_w;
    }
    // Pool (1,1) plays: Winners (2,1), Losers (1,2)
    if (w_st[1][1] + s_st[1][1] > 0) {
        process_matches_in_pool(w_st[1][1], s_st[1][1], w_match_w, w_match_l, s_match_w, s_match_l);
        next_w_st[2][1] += w_match_w; 
        next_w_st[1][2] += w_match_l; 
        next_s_st[2][1] += s_match_w; 
        next_s_st[1][2] += s_match_l; 
    }
    w_st = next_w_st;
    s_st = next_s_st;
    next_w_st.assign(4, std::vector<int>(4, 0));
    next_s_st.assign(4, std::vector<int>(4, 0));

    // --- Round 4 ---
    // Pool (2,1) plays: Winners (3,1) qualify, Losers (2,2)
    if (w_st[2][1] + s_st[2][1] > 0) {
        process_matches_in_pool(w_st[2][1], s_st[2][1], w_match_w, w_match_l, s_match_w, s_match_l);
        qualified_weak_teams += w_match_w;
        next_w_st[2][2] += w_match_l;
        next_s_st[2][2] += s_match_l;
    }
    // Pool (1,2) plays: Winners (2,2), Losers (1,3) eliminated
    if (w_st[1][2] + s_st[1][2] > 0) {
        process_matches_in_pool(w_st[1][2], s_st[1][2], w_match_w, w_match_l, s_match_w, s_match_l);
        next_w_st[2][2] += w_match_w; 
        // eliminated_weak_teams += w_match_l;
        next_s_st[2][2] += s_match_w; 
    }
    w_st = next_w_st;
    s_st = next_s_st;
    next_w_st.assign(4, std::vector<int>(4, 0));
    next_s_st.assign(4, std::vector<int>(4, 0));

    // --- Round 5 ---
    // Pool (2,2) plays: Winners (3,2) qualify, Losers (2,3) eliminated
    if (w_st[2][2] + s_st[2][2] > 0) {
        process_matches_in_pool(w_st[2][2], s_st[2][2], w_match_w, w_match_l, s_match_w, s_match_l);
        qualified_weak_teams += w_match_w;
        // eliminated_weak_teams += w_match_l;
        // s_match_w would qualify, s_match_l eliminated. No further state needed.
    }
    // Tournament ends.

    std::cout << qualified_weak_teams << std::endl;

    return 0;
}