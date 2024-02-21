#include <iostream>
#include <vector>


int calBae(const std::vector<bool>& t) {
    int count = 0;
    for (const auto &e: t)
        if (e == true) count++;
    return count;
}

char getPairName(int n) {
    switch (n) {
        case 0:
            return 'D';
        case 1:
            return 'C';
        case 2:
            return 'B';
        case 3:
            return 'A';
        case 4:
            return 'E';
        default:
            return 'X';
    }
}


int main(void) {
    const int testcases = 3;
    const int pairs = 4;
    for (int i = 0; i < testcases; i++) {
        std::vector<bool> t(pairs, false);
        for (int j = 0; j < pairs; j++) {
            int ti;
            std::cin >> ti;
            if (ti == 1) {
                t[j] = true;
            }
        }
        int numBae = calBae(t);
        std::cout << getPairName(numBae) << std::endl;
    }
    return 0;
}
