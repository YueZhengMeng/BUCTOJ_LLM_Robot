#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    std::cin >> n;
    if (n < 5) {
        std::cout << 2 << std::endl;
    } else if (n < 14) {
        std::cout << 3 << std::endl;
    } else if (n < 31) {
        std::cout << 4 << std::endl;
    } else if (n < 90) {
        std::cout << 5 << std::endl;
    } else if (n < 178) {
        std::cout << 6 << std::endl;
    } else if (n < 375) {
        std::cout << 7 << std::endl;
    } else if (n < 710) {
        std::cout << 8 << std::endl;
    } else if (n < 1302) {
        std::cout << 9 << std::endl;
    } else if (n < 2263) {
        std::cout << 10 << std::endl;
    } else if (n < 4080) {
        std::cout << 11 << std::endl;
    } else if (n < 6801) {
        std::cout << 12 << std::endl;
    } else if (n < 11990) {
        std::cout << 13 << std::endl;
    } else if (n < 20203) {
        std::cout << 14 << std::endl;
    } else if (n < 34904) {
        std::cout << 15 << std::endl;
    } else if (n < 58005) {
        std::cout << 16 << std::endl;
    } else if (n < 99266) {
        std::cout << 17 << std::endl;
    } else {
        std::cout << 18 << std::endl;
    }
    return 0;
}