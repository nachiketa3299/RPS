#include <iostream>
#include <vector>
#include <algorithm>

typedef std::pair<std::size_t, std::size_t> Range;

struct RangeSum {
public:
    Range range;
    std::size_t sum = 0;
    RangeSum(Range range): range(range) {}
};


int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    
    std::size_t N, M; std::cin >> N >> M;
    
    std::vector<std::size_t> vec(N);
    for (auto &e: vec) std::cin >> e;
    
    std::vector<Range> ranges(M);
    for (auto &range: ranges) {
       std::cin >> range.first >> range.second;
       range.first--; range.second--;
    }
    
    for (auto &range: ranges) {
        std::size_t sum = 0;
        for (std::size_t i = range.first; i <= range.second; ++i) {
            sum += vec[i];
        }
        std::cout << sum << '\n';
    }
    
    return 0;
}
