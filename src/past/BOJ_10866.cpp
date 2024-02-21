#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

enum ISCUTE { NO, YES };

bool isJunheeCute(const std::vector<bool> &c_v) {
    int c_cnt = std::count(c_v.begin(), c_v.end(), ISCUTE::YES);
    return c_cnt > c_v.size() - c_cnt ? true : false;
}

int main(void) {
    int N; std::cin >> N;
    std::vector<bool> c_v;
    for (std::size_t i = 0; i < N; ++i) {
        bool in; std::cin >> in;
        c_v.push_back(in);
    }

    if (isJunheeCute(c_v)) {
        std::cout << "Junhee is cute!\n";
    } else {
        std::cout << "Junhee is not cute!\n";
    }
    return 0;
}
