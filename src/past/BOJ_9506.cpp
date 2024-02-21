#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

class Int {
private:
    int value;
public:
    Int(int N): value(N) {}
    bool isComp(void) const {
        int sum = 0;
        for (const auto& d: this->getDivisors()) sum += d;
        return (sum == this->value);
    }

    std::vector<int> getDivisors(void) const {
        std::vector<int> ds;
        int divhalf = int(sqrt(this->value));
        for (int i = 1; i <= divhalf; ++i) {
            if (this->value % i == 0) {
                ds.push_back(i);
                if (i != this->value / i) ds.push_back(this->value / i);
            }
        }
        std::sort(ds.begin(), ds.end());
        return ds;
    }

    std::string toStr(void) const {
        std::string buffer;
        int sum = 0; std::vector<int> ds = this->getDivisors();
        for (const auto &d: ds) sum += d;
        if (sum - this->value == this->value) {
            buffer = std::to_string(this->value);
            for (int i = 0; i < ds.size() - 1; ++i) {
                if (i == 0) buffer += " = " + std::to_string(ds[i]);
                else buffer += " + " + std::to_string(ds[i]);
            }
            buffer += '\n';
        } else {
            buffer = std::to_string(this->value) + " is NOT perfect.\n";
        }
        return buffer;

    }

    friend std::ostream& operator<<(std::ostream& os, const Int& i) {
        os << i.toStr();
        return os;
    }
};

int main(void) {
    std::vector<int> ts;
    for (int i = 0; i != -1; std::cin >> i, ts.push_back(i)); 
    ts.pop_back();
    for (const auto& t: ts) std::cout << Int(t);

}
