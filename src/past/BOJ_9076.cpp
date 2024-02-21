#include <iostream>
#include <vector>
#include <algorithm>

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    const std::size_t SIZE = 5;
    std::vector<std::size_t> vec(SIZE);

    std::size_t T; std::cin >> T;
    for (std::size_t t = 0; t < T; ++t) {
        for (auto &e: vec) std::cin >> e;
        std::sort(vec.begin(), vec.end());

        if (vec[3] - vec[1] >= 4) {
            std::cout << "KIN\n";
        } else {
            std::size_t subtotal = 0;
            for (std::size_t i = 0; i < vec.size(); ++i) {
                if (i != 0 && i != vec.size() - 1) subtotal += vec[i];
            }
            std::cout << subtotal << '\n';
        }

    }

    return 0;
}
