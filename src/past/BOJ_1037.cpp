#include <iostream>
#include <vector>
#include <algorithm>

int main(void) {
    int n; std::cin >> n;
    std::vector<int> d_vec(n);
    for (std::size_t i = 0; i < n; ++i) 
        std::cin >> d_vec[i];

    std::sort(d_vec.begin(), d_vec.end());
    int N = (*d_vec.begin()) * (*(--d_vec.end()));
    std::cout << N << '\n';

    return 0;
}
