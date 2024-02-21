#include <iostream>
#include <vector>
#include <algorithm>

int main(void) {
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int N; std::cin >> N;
    std::vector<int> to_sort(N);
    for (std::size_t i = 0; i < N; ++i)
        std::cin >> to_sort[i];

    std::sort(to_sort.begin(), to_sort.end());
    for (const int &e: to_sort) 
        std::cout << e << '\n';
    return 0;
}
