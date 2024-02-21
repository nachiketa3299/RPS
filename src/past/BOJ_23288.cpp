#include <iostream>
#include <vector>

struct Position {
    int x, y;
    Position(int x, int y): x(x), y(y) {}
    Position(const Position &pos): x(pos.x), y(pos.y) {}
    void changeDirNegative(void) {
        this->x *= -1; this->y *= -1;
        return;
    }
    friend std::ostream &operator<<(std::ostream &os, const struct Position &pos) {
        os << "(" << pos.x << " , " << pos.y << ")";
        return os;
    }
};

class Dice {
public:
    struct DiceFace {
        int bottom;
        int top;
        int north;
        int south;
        int west;
        int east;
    } face { 1, 6, 2, 5, 4, 3 };
    Position pos;
    Position dir { 1, 0 };
public:
    Dice(void): pos(1, 1) {};
    Dice(const Dice &d): pos(d.pos), face(d.face) {}
    void changeDir(int mod) {
        // c( 90) == 0, s( 90) == 1, c(-90) == 0, s(-90) == -1
        // Clock x' = c( 90)x - s( 90)y; y' = s( 90)x + c( 90)y;
        //-Clock x` = c(-90)x - s(-90)y; y' = s(-90)x + c(-90)y;
        struct Coeff {
            int a, b, c, d;
            Coeff(int a=0, int b=0, int c=0, int d=0): a(a), b(b), c(c), d(d) {}
            //Coeff(const Coeff &r): a(r.a), b(r.b), c(r.c), d(r.d) {}
            Position calNewPos(const Position& pos) {
                int nposx = this->a * pos.x + this->b * pos.y;
                int nposy = this->c * pos.x + this->d * pos.y;
                return Position(nposx, nposy);
            }
        };

        struct Coeff coeff;
        switch(mod) {
            case 90:
                coeff = { 0, -1, 1, 0 };
                break;
            case -90:
                coeff = { 0, 1, -1, 0 };
                break;
            default:
                coeff = { 0, 0, 0, 0 };
        }
        this->pos = coeff.calNewPos(this->pos);
        return;
    }
private:
};

class Map {
private:
    struct MapElement {
        Position pos;
        int value;
        MapElement(void): pos(0, 0), value(0) {}
    };
    std::vector<std::vector<MapElement>> mes;
public:
    Map(int N, int M): mes(N, std::vector<MapElement>(M, MapElement())) {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                this->mes[i][j].pos = { i + 1, j + 1 };
    }
    Map(const Map& m): mes(m.mes) {}

    friend std::istream& operator>>(std::istream &is, Map &m) {
        for (auto &mes: m.mes) {
            for (auto &me: mes)
                is >> me.value;
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream &os, const Map &m) {
        for (const auto &mes: m.mes) {
            for (const auto &me: mes) {
                os << me.pos << " " << me.value << " | ";
            }
            os << "\n";
        }
        return os;
    }
};

class Handler {
private:
    Dice d;
    Map m;
    int commands;
public:
    Handler(const Map &m, const Dice &d, int K): d(d), m(m), commands(K) {}
};

int main(void) {
    int N, M, K; std::cin >> N  >> M >> K;
    Map m(M, N); std::cin >> m;
    Dice d;
    for (int i = 0; i < 4; i++) {
        std::cout << d.dir.x << ", " << d.dir.y << '\n';
        d.changeDir(90);
    }

    for (int i = 0; i < 4; i++) {
        std::cout << d.dir.x << ", " << d.dir.y << '\n';
        d.changeDir(-90);
    }
    Handler h(m, d, K);
}
