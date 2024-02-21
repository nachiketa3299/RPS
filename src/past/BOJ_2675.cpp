#include <iostream>
#include <string>

std::pair<std::size_t, std::string> makePair(const std::string &str) {
    std::size_t space_idx = str.find(' ');
    return { std::stoi(str.substr(0, space_idx)), str.substr(space_idx + 1) };
}

std::string makeNewString(const std::pair<std::size_t, std::string> &sr) {
    std::string rstr = "";
    for (const char &c: sr.second) {
        for (std::size_t i = 0; i < sr.first; ++i) rstr += c;
    }
    return rstr;
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::size_t T; std::cin >> T; std::cin.ignore();
    for (std::size_t i = 0; i < T; ++i) {
        std::string cinput;
        std::getline(std::cin, cinput);
        std::pair<std::size_t, std::string> rep_str = makePair(cinput);
        std::cout << makeNewString(rep_str) << '\n';
    }
}
