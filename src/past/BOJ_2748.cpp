#include <iostream>

int fib(int n) {
    if (n == 0) return 0;
    else if (n == 1) return 1;
    else {
        int a = 0;
        int b = 1;
        int c;
        for (int i = 2; i <= n; i++) {
            c = a + b;
            a = b;
            b = c;
        }
        return c;
    }
}

int main(void) {
    int n;
    std::cin >> n;
    std::cout << fib(n) << std::endl;
    std::cout << "===" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "- " << i << ": " << fib(i) << std::endl;
    }
    return 0;
}
