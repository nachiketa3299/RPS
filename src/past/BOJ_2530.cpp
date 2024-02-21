#include <iostream>

struct Duration {
    int s;
    Duration(int s): s(s) {}
    Duration(const Duration &d): s(d.s) {}
};

struct Time {
    int h, m, s;
    Time(int h, int m, int s): h(h), m(m), s(s) {}
    Time(const Time &t): h(t.h), m(t.m), s(t.s) {}
    Time operator+(const Duration& d) const {
        int nh = this->h;
        int nm = this->m;
        int ns = this->s + d.s;
        while (ns >= 60) {
            ns -= 60;
            ++nm;
        }

        while (nm >= 60) {
            nm -= 60;
            ++nh;
        }

        while (nh >= 24) {
            nh -= 24;
        }
        return Time(nh, nm, ns);
    }
    void print(void) const {
        std::cout << this->h << " ";
        std::cout << this->m << " ";
        std::cout << this->s << std::endl;
        return;
    }
};



int main(void) {
    int h, m, s; std::cin >> h >> m >> s;
    struct Time t(h, m, s);
    int dur; std::cin >> dur;
    struct Duration d(dur);
    Time r = t + d;
    r.print();
}
