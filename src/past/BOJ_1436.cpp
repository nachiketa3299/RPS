#include <iostream>
#include <string>

namespace STR {
    const std::string APO = "666";
}

namespace INT {
    const int APO = 666;
}

int main(void) {
    int N; std::cin >> N;
    int cnt = 0;
    int num = INT::APO;
    while (cnt < N) {
        if (std::to_string(num).find(STR::APO) != std::string::npos) {
            cnt++;
            if (cnt == N) break;
        }
        num++;
    }

    std::cout << std::to_string(num) << '\n';
    return 0;
}
