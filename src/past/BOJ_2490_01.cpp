#include <iostream>
#include <algorithm>
#include <bitset>
#include <vector>

const std::size_t INPUT_NUM = 3;
const std::size_t BITMASK_SIZE = 4;

/*
enum YutMask {
    ONE = (0x01 << 0), // 0001 (1)
    TWO = (0x01 << 1), // 0010 (2)
    THR = (0x01 << 2), // 0100 (4)
    FOU = (0x01 << 3), // 1000 (8)
};
*/
/*
 * YU (D) = 0000 (0)
 * GU (C) = 0001, 0010, 0100, 1000 (1, 2, 4, 8)
 * GA (B) = 0011, 1001, 1010, 1100, 0101, 0111 (3, 9, 10, 12)
 * DO (A) = 1110, 1101, 1011, 0111 (14, 13, 11, 7)
 * MO (E) = 1111 (15)
 */

enum Yut {
    YU,
    GU,
    GA,
    DO,
    MO
};

namespace YutSymbol {
    const std::string YU = "D";
    const std::string GU = "C";
    const std::string GA = "B";
    const std::string DO = "A";
    const std::string MO = "E";
}

std::string eraseWhiteSpace(std::string &str) {
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
    return str;
}

std::string whatIsThis(const std::bitset<BITMASK_SIZE> &bm) {
    int one_count = bm.count();
    std::string return_string;
    switch(one_count) {
        case Yut::YU:
            return_string = YutSymbol::YU;
            break;
        case Yut::GU:
            return_string = YutSymbol::GU;
            break;
        case Yut::GA:
            return_string = YutSymbol::GA;
            break;
        case Yut::DO:
            return_string = YutSymbol::DO;
            break;
        case Yut::MO:
            return_string = YutSymbol::MO;
            break;
    }
    return return_string;
}

void printResult(const std::bitset<BITMASK_SIZE> &bm) {
    std::cout << whatIsThis(bm) << '\n';
}


int main(void) {


    std::vector<std::string> i_vec(INPUT_NUM);
    for (std::string &i: i_vec) std::getline(std::cin, i);

    std::transform(i_vec.begin(), i_vec.end(), i_vec.begin(), eraseWhiteSpace);

    std::vector<std::bitset<BITMASK_SIZE>> b_vec(INPUT_NUM);
    for (std::size_t i = 0; i < INPUT_NUM; ++i) b_vec[i] = std::bitset<BITMASK_SIZE>(i_vec[i]);

    std::for_each(b_vec.begin(), b_vec.end(), printResult);
    return 0;
}


