#include <iostream>
#include <vector>
#include <algorithm>

const std::size_t NUM_OF_STATION = 10;

struct PersonInOut {
    std::size_t in, out;
    PersonInOut(void): in(0), out(0) {}
    std::size_t getNet(void) const { return (this->in - this->out); }
};

std::vector<std::size_t> getAccPersonNumber(const std::vector<PersonInOut> &vec) {
    std::vector<std::size_t> r(NUM_OF_STATION, 0);
    for (std::size_t i = 0; i < NUM_OF_STATION; ++i) {
        if (i == 0) r[i] = vec[i].getNet();
        else        r[i] = r[i - 1] + vec[i].getNet();
    }
    return r;
}

int main(void) {
    std::vector<PersonInOut> pv(NUM_OF_STATION); // person_inout_info_vector
    for (std::size_t i = 0; i < NUM_OF_STATION; ++i) {
        std::cin >> pv[i].out;
        std::cin >> pv[i].in;
    }
    std::vector<std::size_t> ptn = getAccPersonNumber(pv);
    std::cout << *std::max_element(ptn.begin(), ptn.end()) << std::endl;
    return 0;
}
