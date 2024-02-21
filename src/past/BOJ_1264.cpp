#include <iostream>
#include <string>

bool count_cond (const char &c) {
    switch(c) {
        case 'a':
        case 'A':
        case 'e':
        case 'E':
        case 'i':
        case 'I':
        case 'o':
        case 'O':
        case 'u':
        case 'U':
            return true;
        default:
            return false;
    }
}

std::size_t count(const std::string &str) {
    std::size_t cnt = 0;
    for (const auto &c: str)
        if (count_cond(c)) cnt++;
    return cnt;
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::string input; std::getline(std::cin, input);

    while(input != "#") {
        std::cout << count(input) << '\n';
        std::getline(std::cin, input);
    }

    return 0;
}
