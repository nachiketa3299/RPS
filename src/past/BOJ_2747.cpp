#include <iostream>

int fib(int n) {
    if (n == 0 || n == 1) {
        return n;
    } else {
        return fib(n - 2) + fib(n - 1);
    }
}

int fib_i(int n) {
    if (n == 0 || n == 1) {
        return n;
    } else {
        int ci = 2;
        int n2 = 0, n1 = 1;
        int c = 1;
        while (ci != n) {
            ci++;
            n2 = n1;
            n1 = c;
            c = n1 + n2;
        }
        return c;
    }
}

int main(void) {
    int n;
    std::cin >> n;
    std::cout << fib_i(n) << std::endl;
    return 0;
}
