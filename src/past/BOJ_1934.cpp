#include <iostream>

int GCD(int x, int y) {
    if (y == 0) return x;
    else return GCD(y, x % y);
}


int LCM(int x, int y) {
    int G = GCD(x, y);
    return x * y / G;
}

int main(void) {
    int T; std::cin >> T;
    for (std::size_t i = 0; i < T; ++i) {
        int x, y; std::cin >> x >> y;
        std::cout << LCM(x, y) << '\n';
    }
    return 0;
}
