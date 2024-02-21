#include <iostream>
#include <algorithm>
#include <vector>

struct Position {
    int x, y; 
    Position(int x, int y): x(x), y(y) {}
    ~Position(void) {}
    int getVHDistance(const Position &recp) const {
        if (recp.x == this->x) {
            if (recp.y == 0) return this->y;
            else return recp.y - this->y;
        } else {
            if (recp.x == 0) return this->x;
            else return recp.x - this->x;
        }
    }
};

struct Rectangle {
    int w, h;
    Rectangle(int w, int h): w(w), h(h) {}
    ~Rectangle(void) {}
};

class Handler {
private:
    Rectangle *r;
    Position *p;
public:
    Handler(Rectangle *r, Position *p): r(r), p(p) {}
    ~Handler() { delete r; delete p; return; }

    int getMinEscapeDistance(void) const {
        std::vector<int> e_dists = this->getAllEscapeDistance();
        return *std::min_element(e_dists.begin(), e_dists.end());
    }

private:
    std::vector<int> getAllEscapeDistance(void) const {
        std::vector<int> e_dists;
        std::vector<Position> rps = getRectPosVec();
        for (const Position &rp: rps) {
            e_dists.push_back(this->p->getVHDistance(rp));
        }
        return e_dists;
    }

    std::vector<Position> getRectPosVec() const {
        std::vector<Position> ps {
            Position(0, this->p->y),
            Position(this->p->x, this->r->h),
            Position(this->r->w, this->p->y),
            Position(this->p->x, 0),
        };
        return ps;
    }
};

int main(void) {
    int x, y, w, h; std::cin >> x >> y >> w >> h;
    Handler H(new Rectangle(w, h), new Position(x, y));
    std::cout << H.getMinEscapeDistance() << '\n';
}
