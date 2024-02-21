#include <iostream>
#include <vector>

const int POS_NUM = 3;

struct Position2D {
    int x, y;
    Position2D(void): x(0), y(0) {}
    Position2D(int x, int y): x(x), y(y) {}
    friend std::istream& operator>>(std::istream& is, struct Position2D &ref) {
        is >> ref.x >> ref.y; return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const struct Position2D &ref) {
        os << ref.x << " " << ref.y; return os;
    }
};

struct Position2D getRecPos(std::vector<struct Position2D> &p_v) {
    int x_standard, x;
    if (p_v[0].x == p_v[1].x) {
        x_standard = p_v[0].x;
        x = p_v[2].x;
    } else if (p_v[0].x == p_v[2].x) {
        x_standard = p_v[0].x;
        x = p_v[1].x;
    } else {
        x_standard = p_v[1].x;
        x = p_v[0].x;
    }
    
    int y_standard, y;
    if (p_v[0].y == p_v[1].y) {
        y_standard = p_v[0].y;
        y = p_v[2].y;
    } else if (p_v[0].y == p_v[2].y) {
        y_standard = p_v[0].y;
        y = p_v[1].y;
    } else {
        y_standard = p_v[1].y;
        y = p_v[0].y;
    }
    return Position2D(x, y);

}



int main(void) {
    std::vector<struct Position2D> p_v;
    for (std::size_t i = 0; i < POS_NUM; ++i) {
        struct Position2D tp; std::cin >> tp;
        p_v.push_back(tp);
    }
    std::cout << getRecPos(p_v) << std::endl;
}
