#include <iostream>

int getGCD(int a, int b) {
    if (b == 0) return a;
    else return getGCD(b, a % b);
}

int getLCM(int a, int b) {
    return a * b / getGCD(a, b);
}

class CainCalendar{
private:
    int M, N;
public:
    CainCalendar(int M, int N): M(M), N(N) {}

    int getNOfCainYear(int x, int y) const {
        int LCM = getLCM(this->M, this->N);
        for (std::size_t k = 0; x + k * this->M <= LCM; k++) {
            int nth = x + k * this->M;
            int nth_y = nth % this->N;
            if (nth_y == 0) nth_y += N;
            if (nth_y == y) return nth;
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
