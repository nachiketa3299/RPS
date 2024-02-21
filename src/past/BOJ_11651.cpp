#include <iostream>
#include <vector>
#include <algorithm>

struct Position {
    int x, y;
    Position(int x=0, int y=0): x(x), y(y) {}
    friend std::istream &operator>>(std::istream &is, Position &ref) {
        is >> ref.x >> ref.y; return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const Position &ref) {
        os <<  ref.x << " " << ref.y; return os;
    }
};

int main(void) {
    int N;  std::cin >> N;
    std::vector<Position> pos_v(N);
    for (Position &pos: pos_v) std::cin >> pos;
    std::sort(pos_v.begin(), pos_v.end(), [](const Position &ref1, const Position &ref2){
            if  (ref1.y != ref2.y) return  ref1.y < ref2.y;
            else return ref1.x < ref2.x;
        }
    );

    for (const Position &pos: pos_v) std::cout << pos << '\n';

    return 0;
}