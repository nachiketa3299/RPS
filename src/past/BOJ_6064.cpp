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

class Cain {
private:
    int M, N;
public:
    Cain(int M, int N): M(M), N(N) {}

    int getNOfYear(int x, int y) const {
        int LCM = getLCM(this->M, this->N);
        std::vector<int> M_v(LCM, 1), N_v(LCM, 1);

        for (std::size_t i = 1; i < LCM; ++i) {
            if (M_v[i - 1] == this->M) 
                M_v[i] = 1; 
            else 
                M_v[i] = M_v[i - 1] + 1;
            if (N_v[i - 1] == this->N) 
                N_v[i] = 1; 
            else 
                N_v[i] = N_v[i - 1] + 1;
        }

        std::vector<int>::iterator it; int t_idx;

        for (it = M_v.begin(); it != M_v.end(); it = std::find(++it, M_v.end(), x)) {
            t_idx = std::distance(M_v.begin(), it);
            if (N_v[t_idx] == y) return ++t_idx;
        }

        return -1;
    }
};


int main(void) {
    int T; std::cin >> T;

    for (std::size_t i = 0; i < T; ++i) {
        int M, N, x, y; std::cin >> M >> N >> x >> y;
        std::cout << Cain(M, N).getNOfYear(x, y) << '\n';

    }

    return 0;
}
