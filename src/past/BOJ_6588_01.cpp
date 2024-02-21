#include <iostream>
#include <vector>
#include <algorithm>

int main(void) {
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    std::vector<int> inputs;
    while(true) {
        int n; std::cin >> n;
        if (n == 0) break;
        else inputs.push_back(n);
    }
    int max_n = *std::max_element(inputs.begin(), inputs.end());

    std::vector<bool> p_v(max_n + 1, true); 
    p_v[0] = false; p_v[1] = false;
    for (std::size_t i = 2; i < max_n + 1; ++i) {
        if (p_v[i]) {
            for(std::size_t j = i + i; j < max_n + 1; j += i) {
                p_v[j] = false;
            }
        }
    }

    for (const auto &n: inputs) {
        bool found = false;
        for (std::size_t i = 3; i < n; ++i) {
            if (p_v[i] && p_v[n - i]) {
                found = true;
                std::cout << n << " = " << i << " + " << n - i << '\n';
                break;
            }
        }
        if (!found) std::cout << "Goldbach's conjecture is wrong.\n";
    }

    return 0;
}
