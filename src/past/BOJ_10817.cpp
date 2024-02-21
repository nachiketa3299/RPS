#include <vector>
#include <algorithm>
#include <iostream>

struct Triple {
    int a, b, c;
    Triple(void): a(0), b(0), c(0) {}
    friend std::istream& operator>>(std::istream &is, struct Triple& ref) {
        is >> ref.a >> ref.b >> ref.c; return is;
    }
    int getSecondBiggestNumber(void) const {
        std::vector<int> v;
        v.push_back(this->a);
        v.push_back(this->b);
        v.push_back(this->c);
        std::sort(v.begin(), v.end());
        return v[1];
    }
};

int main(void) {
    struct Triple t;
    std::cin >> t;
    std::cout << t.getSecondBiggestNumber() << '\n';
}
