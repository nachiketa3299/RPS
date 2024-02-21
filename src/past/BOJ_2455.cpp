#include <iostream>
#include <algorithm>
#include <vector>
struct StationInfo {
    int out, in;
    StationInfo(int out, int in) : out(out), in(in) {}
    StationInfo(void) : out(0), in(0) {}

    int net(void) {
        return this->in - this->out;
    }
    void print(void) const {
        std::cout << this->out << " " << this->in << std::endl;
        return;
    }
};

int main(void) {
    std::vector<struct StationInfo> si;
    for (int j = 0; j < 4; j++) {
        int i, o;
        std::cin >> o >> i;
        si.push_back(StationInfo(o, i));
    }


    std::vector<int> pPerStation(4, 0);
    pPerStation[0] = si[0].net();
    for (int i = 1; i < 4; i++) {
        pPerStation[i] = pPerStation[i - 1] + si[i].net();
    }

    std::cout << *max_element(pPerStation.begin(), pPerStation.end()) << std::endl;
    return 0;
}
