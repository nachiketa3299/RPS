#include <iostream>
#include <vector>

struct Number {
    const int value;
    std::vector<int> divisors;
    Number(int N): value(N) {
        for (int i = 1; i <= N; i++)
            if (N % i == 0) this->divisors.push_back(i);
        return;
    }
    int getKthDivisor(int K) const {
        if (this->divisors.size() < K) return 0;
        else return this->divisors[K - 1];
    }
};

int main(void) {
    int N, K;
    std::cin >> N >> K;
    std::cout << Number(N).getKthDivisor(K) << std::endl;
    return 0;
}
