#include <iostream>
#include <vector>
        
enum POS { Q1, Q2, Q3, Q4, AXIS , POS_MAX};

struct Position {
public:
    int x, y;
    Position(void): x(0), y(0) {}
    Position(int x, int y): x(x), y(y) {}
    enum POS identify(void) const {
        if (this->x == 0 || this->y == 0) return AXIS;
        else if (this->x > 0 && this->y > 0) return Q1;
        else if (this->x > 0 && this->y < 0) return Q4;
        else if (this->x < 0 && this->y > 0) return Q2;
        else return Q3;
    }
};

int main(void) {

    int n; std::cin >> n;
    std::vector<struct Position> p_v;

    for (std::size_t i = 0; i < n; ++i) {
        int nx, ny; std::cin >> nx >> ny;
        p_v.emplace_back(nx, ny);
    }

    std::vector<std::vector<struct Position>> i_v(POS_MAX);
    for (const Position &p: p_v) i_v[p.identify()].push_back(p);

    for (std::size_t i = 0; i < POS_MAX; ++i) {
        if (i < 4) std::cout << "Q" << i + 1;
        else std::cout << "AXIS";
        std::cout << ": " << i_v[i].size() << '\n';
    }

    return 0;
}
