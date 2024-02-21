#include <iostream>
#include <vector>
#include <algorithm>

int main(void) {
    std::size_t N; std::cin >> N;
    std::vector<int> integers(N);
    for (int &integer: integers) std::cin >> integer;
    int v; std::cin >> v;
    std::cout << std::count(integers.begin(), integers.end(), v) << std::endl;
}
