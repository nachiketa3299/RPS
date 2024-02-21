#include <iostream>

int main(void) {
    int N;
    std::cin >> N;
    int sum = 0;
    for (int i = 0; i < N + 1; i++) {
        for (int j = 0; j <= i; j++) {
            sum += i + j;
        }
    }
    std::cout << sum << std::endl;
    return 0;
}
