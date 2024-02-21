#include <iostream>
#include <vector>

struct Pair {
public:
    const int c;
    const int v;
    int o1;
    int o2;
public:
    Pair(int c, int v) : c(c), v(v), o1(c / v), o2(c % v) {}
public:
    void print(void) const {
        std::cout << "You get ";
        std::cout << o1 << " piece(s) ";
        std::cout << "and your dad gets ";
        std::cout << o2 << " piece(s)." << std::endl;
        return;
    }
};

int main(void) {
    int T;
    std::cin >> T;
    for (int i = 0; i < T; i++) {
        int c, v;
        std::cin >> c >> v;
        struct Pair t = Pair(c, v);
        t.print();
    }

    return 0;
}
