#include <iostream>
#include <string>

const char BLNK = ' ';

std::string trimWhiteSpace(const std::string &str) {
    std::string n_str= str;

    bool fblank = (n_str.front() == BLNK);
    while (fblank) {
        n_str = n_str.substr(1);
        fblank = (n_str.front() == BLNK);
    }

    bool bblank = (n_str.back() == BLNK);
    while (bblank) {
        n_str.pop_back();
        bblank = (n_str.back() == BLNK);
    }
    return n_str;
}

int wCount(const std::string &str)  {
    int w_count = 0;
    int idx = str.find(BLNK, 0);
    while(idx != std::string::npos) {
        w_count++;
        idx = str.find(BLNK, idx + 1);
    }

    if (str.size() != 0) w_count++;
    return w_count;
}

int main(void) {
    std::string input; std::getline(std::cin, input);
    std::cout << wCount(trimWhiteSpace(input)) << '\n';
    return 0;
}
