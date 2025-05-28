/* 
   Count the number of "Friday the 13th" occurrences in a given year 
   using Zeller's Congruence for day-of-week calculation.
*/
#include <bits/stdc++.h>
using namespace std;

// Returns day of week for given y, m, d.
// Zeller's congruence: 0 = Saturday, 1 = Sunday, ..., 6 = Friday
int dayOfWeek(int y, int m, int d) {
    if (m <= 2) {
        m += 12;
        --y;
    }
    int K = y % 100;
    int J = y / 100;
    // Zeller's formula
    int h = (d 
             + (13*(m + 1)) / 5 
             + K 
             + K/4 
             + J/4 
             + 5*J) % 7;
    // h: 0=Saturday,1=Sunday,...,6=Friday
    return h;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int year;
    cin >> year;

    int cntFriday13 = 0;
    for (int month = 1; month <= 12; ++month) {
        // Check if 13th of this month is Friday (h == 6)
        if (dayOfWeek(year, month, 13) == 6) {
            ++cntFriday13;
        }
    }

    cout << cntFriday13 << "\n";
    return 0;
}