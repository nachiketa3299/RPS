#include <iostream>
#include <string>

namespace MARK { const char O = 'O', X = 'X'; };

std::size_t calScore(const std::string &ox_str) {
    std::size_t score = 0;
    std::size_t o_cnt = 0;
    for (const char &c: ox_str) {
        switch(c) {
            case MARK::O: o_cnt++; break;
            case MARK::X: o_cnt = 0; break;
        }
        score += o_cnt;
    }
    return score;
}

int main(void) {
    int T; std::cin >> T;
    for (std::size_t i = 0; i < T; ++i) {
        std::string ox_str; std::cin >> ox_str;
        std::cout << calScore(ox_str) << '\n';
    }
    return 0;
}
