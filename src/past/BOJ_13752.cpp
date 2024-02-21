#include <iostream>
void printHistogram(std::size_t k) {
    for (std::size_t i = 0; i < k; ++i)
        std::cout << "=";
    std::cout << '\n';
    return;
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::size_t n; std::cin >> n;
    for (std::size_t i = 0; i < n; ++i) {
        std::size_t k; std::cin >> k;
        printHistogram(k);
    }
    return 0;
}
