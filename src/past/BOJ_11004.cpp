#include <iostream>
#include <vector>
#include <algorithm>

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    
    std::size_t N, K; std::cin >> N >> K;
    std::vector<int> vec(N);
    for (auto &e: vec) std::cin >> e;
    const auto cmp = [](int x, int y){ return x >= y; };
    
    std::make_heap(vec.begin(), vec.end(), cmp);
    
    for (std::size_t i = 1; i < K; ++i) {
        std::pop_heap(vec.begin(), vec.end(), cmp);
        vec.pop_back();
    }
    std::cout << vec.front() << std::endl;
    return 0;
}
