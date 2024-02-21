#include <iostream>
struct Friends {
    int m, f;
    Friends(int m, int f): m(m), f(f) {}
    friend bool operator!=(const Friends &ref1, const Friends &ref2) {
        return ref1.m != ref2.m || ref1.f != ref2.m;
    }
    int getFriendsSum(void) const {
        return this->m + this->f;
    }
    void printFriendsSum(void) const {
        std::cout << this->getFriendsSum() << '\n';
    }

};

int main(void) {
    while (true) {
        int M, F; std::cin >> M >> F;
        struct Friends f(M, F);
        if (f != Friends(0, 0)) f.printFriendsSum();
        else break;
    }
    return 0;
}
