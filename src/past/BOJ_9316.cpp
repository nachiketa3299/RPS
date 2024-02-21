#include <iostream>

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    std::size_t N; std::cin >> N;
    for (std::size_t i = 0; i < N; ++i) {
        std::cout << "Hello World, Judge " << i + 1 << "!\n";
    }
    
    return 0;
}
