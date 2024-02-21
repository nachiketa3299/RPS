#include <iostream>

struct Time {
    int H, M;
    Time (int h, int m): H(h), M(m) {}

    friend std::ostream& operator<<(std::ostream &os, const Time &ref) {
        os << ref.H << " " << ref.M; return os;
    }
    Time operator-(const Time &ref) {
        int nM = this->M - ref.M; int nH = this->H - ref.H;

        if (nM < 0) { nM += 60; nH--; }
        if (nH < 0) { nH += 24; }

        return { nH, nM };
    }
};

// 0:0 - 1:10 = 22:50
// -1:-10 -> -2:50 -> 22:50

int main(void) {
    int H, M; std::cin >> H >> M;
    Time t(H, M);
    std::cout << t - Time(0, 45) << '\n';
}

