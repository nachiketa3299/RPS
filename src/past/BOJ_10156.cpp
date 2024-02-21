#include <iostream>

int main(void) {
    int K, N, M; std::cin >> K >> N >> M;
    int money = (K * N - M > 0) ? K * N - M : 0;
    std::cout << money << '\n';
    return 0;
}
