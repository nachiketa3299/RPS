#include <iostream>
#include <vector>
#include <algorithm>

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    const auto cmp = [](int x, int y)->bool{ return x >= y; };

    std::size_t N; std::cin >> N;
    std::vector<int> heap;
    std::make_heap(heap.begin(), heap.end(), cmp);
    for (std::size_t i = 0; i < N; ++i) {
        int temp; std::cin >> temp;
        heap.push_back(temp);
        std::push_heap(heap.begin(), heap.end(), cmp);
    }

    for (std::size_t i = 0; i < N; ++i) {
        std::cout << heap.front() << '\n';
        std::pop_heap(heap.begin(), heap.end(), cmp);
        heap.pop_back();
    }

    return 0;
}
