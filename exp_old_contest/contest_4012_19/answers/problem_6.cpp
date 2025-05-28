/* 
   Compute weight from height (cm) and BMI.
   Formula: weight = BMI * (height/100)^2
   Output rounded to 3 decimal places.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double h_cm, bmi;
    cin >> h_cm >> bmi;  // Read height in cm and BMI

    double height_m = h_cm / 100.0;
    double weight = bmi * height_m * height_m;

    // Output with rounding to 3 decimal places
    cout << fixed << setprecision(3) << weight << "\n";
    return 0;
}