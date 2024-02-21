#include <iostream>
#include <vector>
#include <string>

// k is the base

struct Record {
    int y, k;
    Record(int y, int k): y(y), k(k) {}
    Record(void): y(0), k(0) {}
    Record(const Record &r): y(r.y), k(r.k) {}
    int sum(void) const {
        return this->k - this->y;
    }
};

std::string getGameResult(const std::vector<struct Record> &grecords) {
    int total_sum = 0;
    for (const auto& gr: grecords) total_sum += gr.sum();
    if (total_sum > 0) return "Korea";
    else if (total_sum == 0) return "Draw";
    else return "Yonsei";
}

int main(void) {
    const int GNUM = 9;
    int T; std::cin >> T;
    std::vector<std::vector<struct Record>> testcases(T, std::vector<struct Record>(GNUM));

    for (auto &testcase: testcases) {
        for (auto &eachgame: testcase) {
            int y, k; std::cin >> y >> k;
            eachgame = Record(y, k);
        }
    }

    for (auto &testcase: testcases) std::cout << getGameResult(testcase) << '\n';
    return 0;
}
