#include <iostream>

// (R1 + R2) / 2 = S
// R2 = 2S - R1

int getR2(int R1, int S) { return 2 * S - R1; }

int main(void) {
    int R1, S; std::cin >> R1 >> S;
    std::cout << getR2(R1, S) << '\n';
}
