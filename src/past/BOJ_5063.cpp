#include <iostream>
#include <string>
#include <vector>

struct Advertise {
    int r, e, c;
    Advertise(void) {}

    int getNetWorth(void) const {
        int profit_with_ad = this->e - this-> c;
        return this->r - profit_with_ad;
    }

    const std::string resultStr(void) const {
        if (this->getNetWorth() > 0) return "do not advertise";
        else if (this->getNetWorth() < 0) return "advertise";
        else return "does not matter";
    }

    friend std::istream& operator>>(std::istream& is, Advertise &ref) {
        is >> ref.r >> ref.e >> ref.c; return is;
    }

    friend std::ostream& operator<<(std::ostream& os, Advertise &ref) {
        os << ref.resultStr(); return os;
    }
};


int main(void) {
    int N; std::cin >> N;
    std::vector<struct Advertise> a_vec(N);
    for (auto &a: a_vec) { std::cin >> a; std::cout << a << '\n'; }
}
