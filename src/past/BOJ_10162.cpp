#include <iostream>

namespace Time {
    const int A = 300;
    const int B = 60;
    const int C = 10;
    const int BCr = B / C;
    const int ABr = A / B;
}

struct Button {
    int ac; int bc; int cc;
    bool avail;
    Button(int ac, int bc, int cc): ac(ac), bc(bc), cc(cc), avail(true) {}
    Button(bool notavail=false): ac(0), bc(0), cc(0), avail(false) {}

    static struct Button calButtonCount(int T) {
        int tempT = T;
        int ac(0), bc(0), cc(0);

        if (tempT % Time::C != 0) return Button(false);

        cc = tempT / Time::C;
        while (cc >= Time::BCr) {
            cc -= Time::BCr;
            bc += 1;
        }
        while (bc >= Time::ABr) {
            bc -= Time::ABr;
            ac += 1;
        }
        return Button(ac, bc, cc);
    }

    friend std::ostream& operator<<(std::ostream &os, const struct Button btn) {
        if (btn.avail) os << btn.ac << " " << btn.bc << " " << btn.cc << '\n';
        else os  << -1 << '\n';
        return os;
    }
};


int main(void) {
    int T; std::cin >> T;
    std::cout << Button::calButtonCount(T);
    return 0;
}
