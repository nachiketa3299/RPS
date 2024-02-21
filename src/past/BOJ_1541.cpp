#include <iostream>
#include <string>
#include <vector>

const char MINUS = '-';
const char PLUS = '+';

std::vector<std::string> parseMinus(const std::string &str) {
    std::vector<std::string> raw;
    std::string tmp = "";
    for (auto it = str.begin(); it != str.end(); ++it) {
        switch (*it) {
            case MINUS:
                raw.push_back(tmp);
                tmp.clear();
                break;
            default:
                tmp += *it;
                break;
        }
        if (it == str.end() - 1) raw.push_back(tmp);
    }
    /*
    for (const auto &r: raw) {
        std::cout << r << std::endl;
    }
    */
    return raw;
}

std::vector<int> parsePlus(const std::vector<std::string> &r) {
    std::vector<int> vec;
    for (const std::string &s: r) {
        int tmp_sum = 0;
        std::string tmp_e = "";
        for (auto it = s.begin(); it != s.end(); ++it) {
            switch(*it) {
                case PLUS:
                    tmp_sum += std::stoi(tmp_e);
                    tmp_e.clear();
                    break;
                default:
                    tmp_e += *it;
                    break;
            }
            if (it == s.end() - 1) tmp_sum += std::stoi(tmp_e);
        }
        vec.push_back(tmp_sum);
    }
    return vec;
}

int vecSum(const std::vector<int> &vec) {
    int sum = vec.front();
    for(auto it = vec.begin() + 1; it != vec.end(); ++it) sum -= *it;
    return sum;
}

int calMin(const std::string &str) {
    return vecSum(parsePlus(parseMinus(str)));
}

int main(void) {
    std::string input; std::cin >> input;
    std::cout << calMin(input) << std::endl;
    return 0;
}
