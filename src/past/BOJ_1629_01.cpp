#include <iostream>

int main(void) {
    std::size_t A, B, C;
    std::cin >> A >> B >> C;
    unsigned long long int R = 1;
    unsigned long long int m = A % C;
    for (std::size_t i = 0; i < B; ++i) {
        R *= m;
        R %= C;
    }
    std::cout << R << '\n';
    return 0;
}
