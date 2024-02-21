#include <iostream>
#include <vector>
#include <algorithm>

std::size_t countOpToMakeOne(std::size_t N, std::vector<std::size_t> &cache) {
    cache[2] = 1; cache[3] = 1;
    return 0;
}
class OpTree {
// Naming is Op"Tree", but this is not actually a tree.
private:
    std::size_t              n;
    std::vector<std::size_t> cache;
    // `cache[i]` is opereration counts that makes `i` -> 1
public:
    OpTree(std::size_t N): n(N), cache(N + 1, 0) {
        if (n > 1) this->flourish_cache(this->n);
        return;
    }
    std::size_t getMinOpCount(std::size_t idx=0) const {
        if (idx == 0) idx = this->n;
        return this->cache[idx];
    }
private:
    void flourish_cache(std::size_t bound) {
        if (bound > 1) {
            // Base Case Definition #2
            this->cache[2] = 1; // op counts `2` -> 1 is 1
            // Flourishing Cache until `bound`, only in `i` >= 4 case
            for (std::size_t i = 3; i <= bound; ++i) {
                // Operation -1 is always possible
                std::size_t min_op_cnt = this->cache[i - 1] + 1;
                std::size_t to_cmp;
                if (i % 3 == 0) {
                    to_cmp = this->cache[i / 3] + 1;
                    min_op_cnt = (min_op_cnt > to_cmp ? to_cmp : min_op_cnt);
                }
                if (i % 2 == 0) {
                    to_cmp = this->cache[i / 2] + 1;
                    min_op_cnt = (min_op_cnt > to_cmp ? to_cmp : min_op_cnt);
                }
                this->cache[i] = min_op_cnt;
            }
        }
        return;
    }
};

int main(void) {
    std::size_t N; std::cin >> N;
    std::cout << OpTree(N).getMinOpCount() << std::endl;
    return 0;
}
