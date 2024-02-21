#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> getOdd(const std::vector<int>& v) {
    std::vector<int> r_v;
    for (const auto &e: v) {
        if (e % 2 == 1) r_v.push_back(e);
    }
    return r_v;
}

int vSum (const std::vector<int> &v) {
    int sum = 0;
    for (const auto &e: v) {
        sum += e;
    }
    return sum;
}

int main(void) {
    const int n = 7;
    std::vector<int> i_v(n);
    for (int i = 0; i < n; i++) {
        std::cin >> i_v[i];
    }
    std::vector<int> odd_v = getOdd(i_v);
    if (odd_v.size() == 0) std::cout << -1 << std::endl;
    else {
        std::cout << vSum(odd_v) << std::endl;
        std::cout << *std::min_element(odd_v.begin(), odd_v.end()) << std::endl;
    }
    return 0;
}
