#include <iostream>
#include <algorithm>
#include <vector>

int main(void) {
    std::size_t a, b, c; std::cin >> a >> b >> c;
    std::vector<std::size_t> vec { a, b, c };
    std::sort(vec.begin(), vec.end());
    for (const auto &e: vec) std::cout << e << " ";
    std::cout << std::endl;

    return 0;
}
