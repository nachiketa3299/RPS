#include <iostream>
#include <algorithm>

std::size_t getMinZeroCountFact(int n) {
    std::size_t div2cnt = 0, div5cnt = 0;
    // 2 * 5 makes 10 ... count 
    // if n! = K_n * 2^a * 5^b, minimun zero count would be min(a, b)
    // n! = 1 * 2 * ... * (n-1) * n, each element will be variable `target`

    for (std::size_t target = 1; target <= n; ++target) {
        // copy target for div2cnt
        std::size_t tcpy = target; 
        while(true) {
            if (tcpy % 2 == 0) { tcpy /= 2; div2cnt++; }
            else break;
        }
        // copy target for div5cnt
        tcpy = target; 
        while(true) {
            if (tcpy % 5 == 0) { tcpy /= 5; div5cnt++; }
            else break;
        }
    }

    return std::min(div2cnt, div5cnt);
}

int main(void) {
    // Input N
    int N; std::cin >> N;

    std::cout << getMinZeroCountFact(N) << '\n';

    return 0;
}
