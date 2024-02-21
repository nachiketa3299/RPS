#include <iostream>
#include <string>
const char offset = 'A' - 'a';
int main(void) {
    std::string input; std::cin >> input;
    for (std::size_t i = 0; i < input.size(); ++i) {
        if ('a' <= input[i] && input[i] <= 'z') {
            input[i] += offset;
        } else {
            input[i] -= offset;
        }
    }
    std::cout << input << '\n';
    return 0;
}
