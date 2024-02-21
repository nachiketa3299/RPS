#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> getPrimes(int min, int max) {
    std::vector<bool> pv(max + 1, true);
    pv[0] = false, pv[1] = false;

    for (int i = 2; i < pv.size(); i++) {
        if (pv[i] == true) {
            for (int j = i + i; j < pv.size(); j += i) {
                pv[j] = false;
            }
        }
    }

    std::vector<int> p;

    for (int i = min; i <= max; i++)
        if (pv[i] == true) p.push_back(i);

    return p;
}

int sumVec(const std::vector<int> &v) {
    int sum;
    if (v.size() != 0) {
        sum = 0;
        for(const auto &e: v)
            sum += e;
    } else {
        sum = -1;
    }
    return sum;
}

int minVal(const std::vector<int> &v) {
    return *std::min_element(v.begin(), v.end());
}


int main(void) {
    int M, N;
    std::cin >> M;
    std::cin >> N;

    std::vector<int> p = getPrimes(M, N);

    int sum = sumVec(p);
    std::cout << sum << std::endl;
    if (sum != -1) std::cout << minVal(p) << std::endl;

    return 0;
}
