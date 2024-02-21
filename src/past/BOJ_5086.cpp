#include <iostream>
#include <vector>

struct Pair {
    int first, second;
    Pair(void) {}
    Pair(int f, int s): first(f), second(s) {}
    friend std::istream& operator>>(std::istream &is, Pair &ref) {
        is >> ref.first >> ref.second;
        return is;
    }
    bool operator!=(const Pair &ref) {
        return this->first != ref.first && this->second != ref.second;
    }
    const std::string resultStr(void) const {
        const std::string resultOne = "factor";
        const std::string resultTwo = "multiple";
        const std::string resultThree = "neither";

        if (first > second) {
            if (first % second == 0) return resultTwo;
        } else {
            if (second % first == 0) return resultOne;
        }
        return resultThree;
    }
};

int main (void) {
    std::vector<struct Pair> tcs;

    while (true) {
        struct Pair tp; std::cin >> tp;
        if (tp != Pair{0, 0}) tcs.push_back(tp);
        else break;
    }
    for (const auto &tc: tcs) std::cout << tc.resultStr() << '\n';



    return 0;
}
