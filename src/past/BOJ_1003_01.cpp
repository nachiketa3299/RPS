#include <iostream>
#include <algorithm>
#include <vector>

struct CallCount {
    std::size_t zero = 0;
    std::size_t one = 0;
};
typedef std::vector<CallCount> CallCountVec;

class FibCache {
private:
    std::size_t  n;
    CallCountVec cache;
public:
    FibCache(std::size_t N): n(N), cache(N + 1, { 0 , 0 }) {
        this->flourish_cache();
        return;
    }
private:
    void flourish_cache(void) {
        this->cache[0] = { 1, 0 };
        if (this->n > 0) {
            this->cache[1] = { 0, 1 };
            for (std::size_t i = 2; i <= this->n; ++i) {
                const auto &prev  = this->cache[i - 1];
                const auto &pprev = this->cache[i - 2];
                      auto &cur   = this->cache[i];
                cur.zero = prev.zero + pprev.zero;
                cur.one  = prev.one  + pprev.one;
            }
        } 
        return;
    }
public:
    void printCacheByIdx(std::size_t idx) const {
        std::cout << this->cache[idx].zero << " " << this->cache[idx].one << '\n';
        return;
    }
};

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::size_t T; std::cin >> T;
    std::vector<std::size_t> tc_inputs(T);
    for (std::size_t i = 0; i < T; ++i)
        std::cin >> tc_inputs[i];
    std::size_t max_i = *std::max_element(tc_inputs.begin(), tc_inputs.end());
    FibCache fib(max_i);
    for (const auto &tc: tc_inputs) {
        fib.printCacheByIdx(tc);
    }
    return 0;
}
