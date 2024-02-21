#include <iostream>
#include <vector>
#include <algorithm>

void makePrimeTable (std::vector<bool>& pt) {
    pt[1 - 1] = false;
    for (int i = 0; i < pt.size(); i++) {
        if (pt[i] == true) {
            for (int j = 2 * i + 1 ; j < pt.size(); j += i + 1) {
                pt[j] = false;
            }
        } 
    }
}

int main(void) {
    int N;
    std::cin >> N;
    std::vector<int> ins(N, 0);
    for (int i = 0; i < N; i++) {
        int t;
        std::cin >> t;
        ins[i] = t;
    }
    std::vector<bool> pt(*max_element(ins.begin(), ins.end()), true);
    makePrimeTable(pt);


    int nofprimes = 0;
    for (const auto& e: ins) {
        if (pt[e - 1]) nofprimes++;
    }
    std::cout << nofprimes << std::endl;

    return 0;
}
