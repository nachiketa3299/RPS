#include <iostream>

struct Pair {
public:
    const int a;
    const int b;
    const int sum;
public:
    Pair(int a, int b) : a(a), b(b), sum(a + b) {}
public:
    void print(int idx) const {
        std::cout << "Case " << idx << ": ";
        std::cout << this->sum << std::endl;
        return;
    }
};

int main(void) {
    int T;
    std::cin >> T;
    for (int i = 0; i < T; i++) {
        int a, b;
        std::cin >> a >> b;
        struct Pair t = Pair(a, b);
        t.print(i + 1);
    }
    return 0;
}
