#include <iostream>
#include <vector>

int sumVec (const std::vector<int> &v) {
    int sum = 0;
    for (const auto &e: v) {
        sum += e;
    }
    return sum;
}

int main(void) {
    int T;
    std::cin >> T;
    std::vector<std::vector<int>> testcases(T);
    for (int i = 0; i < T; i++) {
        int N;
        std::cin >> N;
        testcases[i].resize(N);
        for (int j = 0; j < N; j++) {
            int temp;
            std::cin >> temp;
            testcases[i][j] = temp;
        }
    }

    for (const auto& t: testcases) {
        std::cout << sumVec(t) << std::endl;
    }
    return 0;
}
