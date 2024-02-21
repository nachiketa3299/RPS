#include <iostream>
#include <vector>

int getTotal(const std::vector<int>& m) {
    int total = 0;
    for (int i = 0; i < m.size() - 1; i++) {
        total += m[i] - 1;
    }
    total += m.back();
    return total;
}

int main(void) {
    // Only One Plug
    int N;
    std::cin >> N;
    std::vector<int> multitaps(N, 0);
    for (int i = 0; i < N; i++) {
        std::cin >> multitaps[i];
    }
    std::cout << getTotal(multitaps) << std::endl;


    return 0;
}
