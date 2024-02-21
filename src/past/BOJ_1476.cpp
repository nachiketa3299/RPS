#include <iostream>
#include <algorithm>

struct Year {
    int e, s, m;
    const int e_max = 15, s_max = 28, m_max = 19;
    Year(void): e(0), s(0), m(0) {}

    friend std::istream& operator>>(std::istream &is, Year &ref) {
        is >> ref.e >> ref.s >> ref.m; return is;
    }

    int convert(void) const {
        int esm_max = std::max( { this->e, this->s, this->m } );
        int n;
        for(n = esm_max; ;++n) {
            bool e_cond = (n - this->e) % this->e_max == 0;
            bool s_cond = (n - this->s) % this->s_max == 0;
            bool m_cond = (n - this->m) % this->m_max == 0;
            if (e_cond && s_cond && m_cond) break;
        }

        return n;
    }
};

int main(void) {
    Year y; std::cin >> y;
    std::cout << y.convert() << '\n';
    return 0;
}
