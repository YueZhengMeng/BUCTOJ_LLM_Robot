#include <iostream>
#include <vector>

// Function to check for leap year according to the problem description:
// A year is a leap year if it's divisible by 4 and not by 100,
// or if it's divisible by 100 and also by 400.
bool is_leap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int target_year;
    std::cin >> target_year;

    // Define days of the week numerically:
    // Sunday = 0, Monday = 1, Tuesday = 2, Wednesday = 3, Thursday = 4, Friday = 5, Saturday = 6
    
    // Reference: Jan 1, 2024, was a Monday (1).
    // (Derived from May 26, 2024, being Sunday (0):
    // Days in 2024 (leap) before May 26: Jan(31)+Feb(29)+Mar(31)+Apr(30) = 121.
    // May 26 is the 121+26 = 147th day.
    // Day of Jan 1 = (Day of May 26 - (147-1) % 7 + 7) % 7
    // Day of Jan 1 = (0 - (146 % 7) + 7) % 7 = (0 - 6 + 7) % 7 = 1)
    int known_year_jan1_day = 1; // Monday for Jan 1, 2024
    int known_year = 2024;

    int day_of_week_jan1_target_year = known_year_jan1_day;

    // Calculate the day of the week for January 1st of the target_year
    if (target_year > known_year) {
        for (int y = known_year; y < target_year; ++y) {
            // A common year has 365 days (365 % 7 = 1). A leap year has 366 days (366 % 7 = 2).
            // The day of the week for Jan 1st of the next year shifts by this amount.
            int shift = is_leap(y) ? 2 : 1;
            day_of_week_jan1_target_year = (day_of_week_jan1_target_year + shift) % 7;
        }
    } else if (target_year < known_year) {
        for (int y = known_year - 1; y >= target_year; --y) {
            // To go back one year from (y+1) to y, we subtract the shift caused by year y.
            int shift = is_leap(y) ? 2 : 1;
            // (current_day - shift_val + 7) % 7 ensures positive result for modulo.
            day_of_week_jan1_target_year = (day_of_week_jan1_target_year - shift + 7) % 7;
        }
    }
    // If target_year == known_year, day_of_week_jan1_target_year is already correct.

    // Standard days in month (non-leap year for Feb initially)
    // Index 0 is unused, month 1 is January, ..., month 12 is December
    std::vector<int> days_in_month_arr = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (is_leap(target_year)) {
        days_in_month_arr[2] = 29; // February has 29 days in a leap year
    }

    int friday_13_count = 0;
    int current_day_of_week_for_1st_of_month = day_of_week_jan1_target_year;

    // Iterate through each month of the target year
    for (int month = 1; month <= 12; ++month) {
        // The 1st of the current month is `current_day_of_week_for_1st_of_month`.
        // The 13th of the month is 12 days after the 1st.
        // So, day of week for the 13th = (day_of_week_for_1st_of_month + 12) % 7.
        int day_of_week_for_13th = (current_day_of_week_for_1st_of_month + 12) % 7;
        
        if (day_of_week_for_13th == 5) { // 5 represents Friday (Sunday=0, ..., Friday=5)
            friday_13_count++;
        }

        // Update `current_day_of_week_for_1st_of_month` for the 1st of the *next* month.
        // This is done by adding the number of days in the current month.
        current_day_of_week_for_1st_of_month = (current_day_of_week_for_1st_of_month + days_in_month_arr[month]) % 7;
    }

    std::cout << friday_13_count << std::endl;

    return 0;
}