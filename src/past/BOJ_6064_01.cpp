#include <iostream>
#include <vector>
#include <algorithm>

int getGCD(int a, int b) {
    if (b == 0) return a;
    else return getGCD(b, a % b);
}

int getLCM(int a, int b) {
    return a * b / getGCD(a, b);
}
struct CainYear {
    int x, y;
    CainYear(int x, int y): x(x), y(y) {}
    friend bool operator==(const CainYear &ref1, const CainYear &ref2) {
        return ref1.x == ref2.x && ref1.y == ref2.y;
    }
    friend bool operator!=(const CainYear &ref1, const CainYear &ref2) {
        return ref1.x != ref2.x || ref1.y != ref2.y;
    }
};

class CainCalendar{
private:
    int M, N;
public:
    CainCalendar(int M, int N): M(M), N(N) {}

    CainYear getNthCainYear(int n) const {
        int x = n % this->M; int y = n % this->N;
        if (x == 0) x = M;
        if (y == 0) y = N;
        return CainYear(x, y);
    }

    int getNOfCainYear(int x, int y) const {
        int LCM = getLCM(this->M, this->N);
        for (std::size_t i = 0; CainYear(x, y) != CainYear(this->M, this->N); ++i) {
            if (CainYear(x, y) == getNthCainYear(i + 1)) return (i + 1);
        }
        return -1;
    }
};


int main(void) {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
    int T; std::cin >> T;

    for (std::size_t i = 0; i < T; ++i) {
        int M, N, x, y; std::cin >> M >> N >> x >> y;
        std::cout << CainCalendar(M, N).getNOfCainYear(x, y) << '\n';

    }

    return 0;
}
