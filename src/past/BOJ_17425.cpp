#include <iostream>
#include <vector>
#include <algorithm>

int main(void) {
    std::ios::sync_with_stdio(false); 
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int T; std::cin >> T;
    std::vector<int> inputs(T);

    for (std::size_t i = 0; i < T; ++i)
        std::cin >> inputs[i];

    int max_input = *std::max_element(inputs.begin(), inputs.end());

    std::vector<long long int> fs(max_input + 1, 1);
    for (std::size_t i = 2; i < fs.size(); ++i) {
        for (std::size_t j = i; j < fs.size(); j += i) {
            fs[j] += i;
        }
    }

    std::vector<long long int> &gs = fs;


    for (std::size_t i = 2; i < gs.size(); ++i) {
        gs[i] += gs[i - 1];
    }

    for (std::size_t i = 0; i < inputs.size(); ++i)
        std::cout << gs[inputs[i]] << '\n';

}

/*
 fs[1] = 1
 fs[2] = 1 + 2
 fs[3] = 1 +    + 3
 fs[4] = 1 + 2      + 4
 fs[5] = 1 +            + 5
 fs[6] = 1 + 2  + 3         + 6
 fs[7] = 1                      + 7
 fs[8] = 1 + 2      + 4             + 8
 */

/*
 gs[1] = fs[1]
 gs[2] = (fs[1]) + fs[2]
 gs[3] = (fs[1] + fs[2]) + fs[3]
 */

