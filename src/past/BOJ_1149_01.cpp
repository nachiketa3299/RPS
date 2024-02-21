#include <iostream>
#include <vector>
#include <algorithm>

enum Colors { R=0, G=1, B=2 };

int main(void) {
    std::size_t N; std::cin >> N;
    
    std::vector<std::vector<std::size_t>> colors(N, std::vector<std::size_t>(3));
    for (auto &color :colors) std::cin >> color[R] >> color[G] >> color[B];
    
    std::vector<std::vector<std::size_t>> cache(3, std::vector<std::size_t>(N));
    cache[R][0] = colors[0][R];
    cache[G][0] = colors[0][G];
    cache[B][0] = colors[0][B];
    
    for (std::size_t i = 1; i < N; ++i) {
        cache[R][i] = std::min(cache[G][i - 1], cache[B][i - 1]) + colors[i][R];
        cache[G][i] = std::min(cache[R][i - 1], cache[B][i - 1]) + colors[i][G];
        cache[B][i] = std::min(cache[R][i - 1], cache[G][i - 1]) + colors[i][B];
    }
    std::cout << std::min({cache[R][N - 1], cache[G][N - 1], cache[B][N - 1]}) << std::endl;
    return 0;
}
