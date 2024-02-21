#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> getPrimeNumbersUntil(int N) {
    std::vector<bool> eras(N + 1, true); 
    eras[0] = false; eras[1] = false;
    for (std::size_t i = 2; i < eras.size(); ++i) {
        if (eras[i] == true) {
            for (std::size_t j = i + i; j < eras.size(); j += j) { eras[j] = false; }
        }
    }
    std::vector<int> p_vec;
    for (std::size_t i = 0; i < eras.size(); ++i) if (eras[i]) p_vec.push_back(i);
    return p_vec;
}

std::vector<int> factorization(int N) {
    std::vector<int> fr_v;
    for (const int &p: getPrimeNumbersUntil(N)) {
        while (true) {
            if (N % p == 0) { N /= p; fr_v.push_back(p); }
            else { break; }
        }
    }
    std::sort(fr_v.begin(), fr_v.end());
    return fr_v;
}

int main(void) {
    int N; std::cin >> N;
    std::vector<int> fr_v = factorization(N);
    if (fr_v.size() != 0) { for (const int &fr: fr_v)  { std::cout << fr << '\n'; } } 

    return 0;
}
