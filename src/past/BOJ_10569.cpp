#include <iostream>

struct Polygon {
public:
    const int v;
    const int e;
    const int f;
public:
    Polygon(int v, int e) : v(v), e(e), f(2 - v + e) {}
public:
    void print(void) const {
        std::cout << this->f << std::endl;
        return;
    }
};

int main (void) {
    int T;
    std::cin >> T;
    for (int i = 0; i < T; i++) {
        int v, e;
        std::cin >> v >> e;
        struct Polygon t = Polygon(v, e);
        t.print();
    }
    return 0;
}
