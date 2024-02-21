#include <iostream>
#include <string>
#include <vector>

int main(void) {
    std::string tstring = "";
    std::vector<std::size_t> cnts('z' - 'a' + 1, 0);
    while(!std::cin.eof()) {
        std::string temp_string;
        std::getline(std::cin, temp_string);
        tstring += temp_string;
    }
    for (const char &c: tstring) {
        if (c >= 'a' && c <= 'z') cnts[c - 97]++;
    } 
    std::vector<char> max_chars;
    std::size_t cmax = 0;
    for (const std::size_t &cnt: cnts) {
        if (cnt > cmax) {
            cmax = cnt;
            max_chars.clear();
            max_chars.push_back(&cnt - &cnts[0] + 97);
        } else if (cnt == cmax) {
            max_chars.push_back(&cnt - &cnts[0] + 97);
        } else {
            ;
        }
    }

    for (const char &c: max_chars) std::cout << c;

    return 0;
}
