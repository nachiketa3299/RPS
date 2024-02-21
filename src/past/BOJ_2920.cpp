#include <iostream>
#include <vector>
#include <string>

enum STATE { ASC, DSC, MIX };
enum SCALE { c=1, d, e, f, g, a, b, C };

bool isASC(const std::vector<int> &vec) {
    bool r = true;
    for (std::size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] != i + 1) {
            r = false;
            break;
        }
    }
    return r;
}

bool isDSC(const std::vector<int> &vec) {
    bool r = true;
    for (std::size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] != vec.size() - i) {
            r = false;
            break;
        }
    }
    return r;
}


int main(void) {
    const int SCALENUM = 8;
    std::vector<int> scale(SCALENUM);
    for (std::size_t i = 0; i < SCALENUM; ++i)
        std::cin >> scale[i];

    STATE state;

    if (scale[0] == SCALE::c) {
        if (isASC(scale)) state = ASC;
        else state = MIX;
    } else if (scale[0] == SCALE::C) {
        if (isDSC(scale)) state = DSC;
        else state = MIX;
    } else {
        state = MIX;
    }
    std::string to_print;

    switch(state) {
        case ASC:
            to_print = "ascending";
            break;
        case DSC:
            to_print = "descending";
            break;
        case MIX:
            to_print = "mixed";
            break;
    }
    std::cout << to_print << '\n';
    return 0;
}
