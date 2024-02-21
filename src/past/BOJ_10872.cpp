#include <iostream>

int factorial(int n) {
    if (n <= 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main(void) {
    int N;
    std::cin >> N;
    std::cout << factorial(N) << std::endl;
    return 0;
}
