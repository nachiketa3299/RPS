#include <iostream>
#include <vector>

struct Domino {
    int head, tail;
    Domino(void): head(0), tail(0) {}
    Domino(int h, int t): head(h), tail(t) {}
    void setNumber(int h, int t) {
        this->head = h;
        this->tail = t;
        return;
    }
    int sumNumber(void) const {
        return this->head + this->tail;
    }
};

struct DominoSet {
    std::vector<struct Domino> d;
    DominoSet(int N) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j <= i; j++) {
                this->d.push_back(Domino(i, j));
            }
        }
        return;
    }
    int sumAllNumbers(void) const {
        int sum = 0;
        for (const auto& d: this->d) {
            sum += d.sumNumber();
        }
        return sum;
    }
};

int main(void) {
    int N;
    std::cin >> N;
    struct DominoSet ds(N + 1);
    std::cout << ds.sumAllNumbers() << std::endl;
    return 0;
}
