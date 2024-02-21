#include <iostream>
#include <vector>
#include <algorithm>

int main(void) {
    int N; std::cin >> N;
    std::vector<int> nums(N);
    for (std::size_t i = 0; i < N; ++i) {
        std::cin >> nums[i];
    }

    int min = *std::min_element(nums.begin(), nums.end());
    int max = *std::max_element(nums.begin(), nums.end());
    std::cout << min << " " << max << '\n';

}
