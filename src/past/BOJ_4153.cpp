#include <iostream>
#include <algorithm>
#include <vector>

struct Triangle {
    std::size_t a, b, c;
    Triangle(std::size_t a, std::size_t b, std::size_t c): a(a), b(b), c(c) {}
    Triangle(void): a(0), b(0), c(0) {}
    friend std::istream &operator>>(std::istream &is, Triangle &ref) {
        is >> ref.a >> ref.b >> ref.c; return is;
    }
    bool isAllZero(void) const {
        return this->a == 0 && this->b == 0 && this->c == 0;
    }

    bool isVTriangle(void) const {
        std::vector<std::size_t> vec { this->a, this->b, this->c };
        std::sort(vec.begin(), vec.end());
        return vec[0]*vec[0] + vec[1]*vec[1] == vec[2]*vec[2];
    }
};

int main(void) {
    while (true) {
        Triangle t; std::cin >> t;
        if (t.isAllZero()) break;
        std::cout << (t.isVTriangle() ? "right" : "wrong") << '\n';
    }
    return 0;
}