#include <iostream>
#include <string>
#include <unordered_map>

bool isNumber(const std::string &str) {
    char fchar = str.front();
    bool cond1 = fchar >= 'a' && fchar <= 'z';
    bool cond2 = fchar >= 'A' && fchar <= 'Z';
    return cond1 || cond2;
}

int main(void) {
    std::ios::sync_with_stdio(false); 
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int N, M; std::cin >> N >> M;
    // N is n of pocketmon
    // M is n of p
    
    std::unordered_map<std::string, std::size_t> ston;
    std::unordered_map<std::size_t, std::string> ntos;
    for (std::size_t pck_numb = 1; pck_numb <= N; ++pck_numb) {
        std::string pck_name; std::cin >> pck_name;
        ston[pck_name] = pck_numb;
        ntos[pck_numb] = pck_name;
    }

    for (std::size_t i = 0; i < M; ++i) {
        std::string pin; std::cin >> pin;
        if (!isNumber(pin)) {
            std::cout << ntos[std::stoi(pin)] << '\n';
        } else {
            std::cout << ston[pin] << '\n';
        }
    }

    return 0;
}
