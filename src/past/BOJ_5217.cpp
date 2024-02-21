#include <iostream>
#include <vector>

std::vector<std::pair<std::size_t, std::size_t>> getSumPairOf(std::size_t n) {
    std::vector<std::pair<std::size_t, std::size_t>> pair_vec;
    for (std::size_t i = 1; i <= n / 2; ++i) {
        std::size_t j = n - i;
        if (i + j == n && i != j) pair_vec.push_back(std::pair<std::size_t, std::size_t> { i, j });
    }
    return pair_vec;

}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::size_t T; std::cin >> T;
    for (std::size_t i = 0; i < T; ++i) {
        std::size_t n; std::cin >> n;
        auto pairs = getSumPairOf(n);
        std::cout << "Pairs for " << n << ": ";
        for (const auto &p: pairs) {
            std::cout << p.first << " " << p.second;
            if (&p - &pairs[0] != pairs.size() - 1) std::cout << ", ";
        }
        std::cout << '\n';
    }
}
