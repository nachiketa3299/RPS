#include <iostream>
#include <string>
#include <algorithm>

namespace CAND {
    std::string P1 = "A", P2 = "B", DRAW = "Tie";
}

struct Result {
    const int vn; const std::string vote;
    const int ac, bc;
    Result(const int vn, const std::string& vote_str)
        : vn(vn), 
          vote(vote_str),
          ac(std::count(vote_str.cbegin(), vote_str.cend(), CAND::P1.c_str()[0])),
          bc(std::count(vote_str.cbegin(), vote_str.cend(), CAND::P2.c_str()[0])) {}
    const std::string resultStr(void) const {
        if (this->ac > this->bc) return CAND::P1;
        else if (this->ac < this->bc) return CAND::P2;
        else return CAND::DRAW;
    }
};

int main(void) {
    int V; std::cin >> V;
    std::string vote; std::cin >> vote;
    std::cout << Result(V, vote).resultStr() << '\n';
}
