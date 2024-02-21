#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>

int getTotalDigit(int n) {
    int digit = 0;
    while(n != 0) { n /= 10; digit++; }
    return digit;
}
int getDigit(int n, int idx) {
    std::string n_str = std::to_string(n);
    return n_str[n_str.size() - idx - 1] - '0';
}

std::vector<int> getClosestWithBrokenButton(int n, const std::vector<bool> &broken) {
    std::vector<int> n_ps;
    int digit_n = getTotalDigit(n);
    std::vector<int> digit_cand;
    for (std::size_t i = digit_n - 1; i <= digit_n + 1; ++i)
        if (i >= 1 && i <= 6) digit_cand.push_back(i);

    return n_ps;
}

int getMinButtonCount(int cur, int n, const std::vector<bool> &broken) {
    if (broken.size() == 0)
        return std::min(abs(n - cur), getTotalDigit(n));
    else {
        std::vector<int> n_ps = getClosestWithBrokenButton(n, broken);
        std::vector<int> cnts;
        for (std::size_t i = 0; i < n_ps.size(); ++i) {
            cnts.push_back(getTotalDigit(n_ps[i]) + abs(n - n_ps[i]));
        }
        return *std::min_element(cnts.begin(), cnts.end());
    }
}



int main(void) {
    const int C = 100;
    int N; std::cin >> N;
    int b_b_n; std::cin >> b_b_n; // broken button numbers

    std::vector<bool> broken(10, false);
    for (std::size_t i = 0; i < b_b_n; ++i) {
        int broken_num; std::cin >> broken_num; 
        broken[broken_num] = true;
    }

    std::cout << getMinButtonCount(C, N, broken) << '\n';




    return 0;
}
