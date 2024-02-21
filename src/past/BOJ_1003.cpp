#include <iostream>
#include <vector>

class Fib {
private:
    std::vector<std::vector<std::size_t>> cnt;
    std::size_t n;
public:
    Fib(std::size_t n): cnt(n + 1, std::vector<std::size_t>(2, 0)), n(n) {
        if (n >= 0) this->cnt[0] = { 1, 0 };
        if (n >= 1) this->cnt[1] = { 0, 1 };
        if (n >= 2) this->memFib();
        return;
    };
private:
    void memFib(void) {
        for(std::size_t tn = 2; tn <= this->n; ++tn) {
            this->cnt[tn][0] = this->cnt[tn-1][0] + this->cnt[tn-2][0];
            this->cnt[tn][1] = this->cnt[tn-1][1] + this->cnt[tn-2][1];
        }
        return;
    }

public:
    void print(void) const {
        std::cout << this->cnt[this->n][0] << " "
                  << this->cnt[this->n][1] << '\n';
        return;
    }
};

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int T; std::cin >> T;
    for (std::size_t i = 0; i < T; ++i) {
        std::size_t n; std::cin >> n;
        Fib(n).print();
    }
    return 0;
}

/*
1 1 2 3 5 8 13 21 34 55 ...
이건데?

f(0) = 0 (1, 0)
f(1) = 1 (0, 1)
f(2) = f(1) + f(0) (1, 1)
f(3) = f(2) + f(1) = {f(1) + f(0)} + f(1) (1, 2)
f(4) = f(3) + f(2) = {f(1) + f(0) + f(1)} + {f(1) + f(0)} (2, 3)
*/
