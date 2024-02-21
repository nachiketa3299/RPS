#include <iostream>
#include <string>
#include <vector>

int makeVerifyNum (const std::vector<int>& in_vec) {
    int verify_num = 0;
    for (auto& e: in_vec) {
        verify_num += e * e;
    }
    return verify_num % 10;
}

int main(void) {
    std::string input;
    std::getline(std::cin, input);
    std::vector<int> in_vec;
    for (const auto& c: input) {
        if (c != ' ') {
            in_vec.push_back(c - '0');
        }
    }

    int verify_num = makeVerifyNum(in_vec);
    std::cout << verify_num << std::endl;

    return 0;
}
