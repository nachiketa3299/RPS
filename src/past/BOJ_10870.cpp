#include <iostream>
#include <vector>

class Fib {
    typedef std::vector<std::size_t> Cache;
private:
    std::size_t n;
    Cache cache;
public:
    Fib(std::size_t n): n(n), cache(n + 1, 0) {
        this->flourish_cache();
        return;
    }
    std::size_t getValue(std::size_t idx=0) {
        if (idx == 0) return this->cache[this->n];
        else          return this->cache[idx];
    }
private:
    void flourish_cache(void) {
        if (this->n == 0) this->cache[0] = 0;
        if (this->n == 1) this->cache[1] = 1;
        if (this->n == 0 || this->n == 1) return;

        this->cache[0] = 0; this->cache[1] = 1;
        for (std::size_t c = 2; c <= this->n; ++c) {
            this->cache[c] = this->cache[c - 1] + this->cache[c - 2];
        }
        return;
    }
};

int main(void) {
    std::size_t n; std::cin >> n;
    std::cout << Fib(n).getValue() << std::endl;
    return 0;
}
