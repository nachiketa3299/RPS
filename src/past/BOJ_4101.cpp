#include <iostream>
#include <vector>

struct Pair {
public:
    int first, second;
    Pair(void): first(0), second(0) {}
    Pair(int f, int s): first(f), second(s) {}
    bool isFirstOneBigger(void) const {
        return this->first > this->second;
    }
    std::string resultStr(void) const {
        return ((this->isFirstOneBigger()) ? "Yes" : "No");
    }
    friend std::istream &operator>>(std::istream &is, struct Pair &ref) {
        is >> ref.first >> ref.second; return is;
    }
    friend bool operator==(const struct Pair &ref1, const struct Pair &ref2) {
        return ref1.first == ref2.first && ref1.second == ref2.second;
    }
    friend std::ostream &operator<<(std::ostream &os, const struct Pair &ref) {
        os << ref.resultStr(); return os;
    }
};

int main(void) {
    std::vector<struct Pair> v;
    while (true) {
        struct Pair tp; std::cin >> tp;
        if (tp == Pair(0, 0)) break;
        else v.push_back(tp);
    }

    for (const auto &p :v) std::cout << p << '\n';

    return 0;
}
