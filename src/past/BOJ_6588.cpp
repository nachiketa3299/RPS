#include <iostream>
#include <vector>
struct Pair {
    int a, b;
    Pair(int a, int b): a(a), b(b) {}
    Pair(void): a(0), b(0) {}
    bool isGBTrue(void) const {
        if (this->a == 0 && this->b == 0) return false;
        else return true;
    }
    friend std::ostream &operator<<(std::ostream &os, const Pair &ref) {
        if (ref.isGBTrue())
            os << ref.a + ref.b << " = " << ref.a << " + " << ref.b;
        else
            os << "Goldbach's conjecture is wrong.";
        return os;
    }
};

std::vector<bool> getPrimeTable(int bound) {
    // bound 이하의 소수를 구한다.
    std::vector<bool> p_v(bound + 1, true);
    p_v[0] = false; p_v[1] = false;
    for (std::size_t i = 2; i < bound + 1; ++i) {
        if (p_v[i]) {
            for (std::size_t j = i + i; j < bound + 1; j += i) {
                p_v[j] = false;
            }
        }
    }

    return p_v;
}

Pair findPrimePair(const std::vector<bool> &p_v, int n) {
    for (std::size_t i = 3; i < p_v.size() / 2; ++i) {
        if (p_v[i]) {
            if (p_v[n - i]) {
                return Pair(i, n - i);
            }
        }
    }
    return Pair();
}


void printGoldBach(int n) {
    Pair p = findPrimePair(getPrimeTable(n), n);
    std::cout << p << '\n';
    return;
}

int main(void) {
    std::ios::sync_with_stdio(false); std::cin.tie(NULL);
    while (true) {
        int n; std::cin >> n;
        if (n == 0) break;
        printGoldBach(n);
    }
    return 0;
}
