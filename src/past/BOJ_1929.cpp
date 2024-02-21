#include <iostream>
#include <vector>

std::vector<bool> getPrimeTable(int bound) {
    std::vector<bool> p_t(bound + 1, true);
    p_t[0] = false; p_t[1] = false;
    for (std::size_t i = 2; i < bound + 1; ++i) {
        if (p_t[i] == true) {
            for (std::size_t j = i + i; j < bound + 1; j += i) p_t[j] = false;
        }
    }
    return p_t;
}

void printBoolVecBetween(const std::vector<bool> &v, int M, int bound) {
    for (std::size_t i = M; i < bound; ++i)
        if (v[i]) std::cout << i << '\n';
    return;
}



int main(void) {
    int M, N; std::cin >> M >> N;
    std::vector<bool> prime_table = getPrimeTable(N);
    printBoolVecBetween(prime_table, M, N + 1);
    return 0;
}
