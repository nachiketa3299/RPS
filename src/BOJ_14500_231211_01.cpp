#include <iostream>
#include <vector>
#include <algorithm>


const std::size_t NUM_POL = 4;

struct Position {
    int x, y;
    Position(int x, int y): x(x), y(y) {}
    Position(void): x(0), y(0) {}
    friend bool operator==(const Position &ref1, const Position &ref2) {
        return ref1.x == ref2.x && ref1.y == ref2.y;
    }
};

class Polyomino {
public:
    std::vector<Position> coords;
public:
    Polyomino(std::vector<Position> p): coords(p) {}
    const std::vector<Position> &getCubicCoords(void) const {
        return this->coords;
    }
};

const std::vector<Polyomino> T_v { 
    {
        /*
         * ( 0, 0)( 1, 0)
         * ( 0,-1)( 1,-1)
         */

        {{{ 0, 0 }, { 1, 0 }, { 0,-1 }, { 1,-1 }}},
        /*
         * ( 0, 0)( 1, 0)( 2, 0)( 3, 0)
         */
        /*
         * ( 0, 0)
         * ( 0,-1)
         * ( 0,-2)
         * ( 0,-3)
         */

        {{{ 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 }}}, {{{ 0, 0 }, { 0,-1 }, { 0,-2 }, { 0,-3 }}},

        /*
         * ( 0, 0)
         * ( 0,-1)
         * ( 0,-2)( 1,-2)
         */
        /*
         * (-2, 0)(-1, 0)( 0, 0)
         * (-2,-1)
         */
        /*
         * (-1 ,0)( 0, 0)
         *        ( 0,-1)
         *        ( 0,-2)
         */
        /*
         *               ( 2, 1)
         * ( 0, 0)( 1, 0)( 2, 0)
         */

        {{{ 0, 0 }, { 0,-1 }, { 0,-2 }, { 1,-2 }}}, {{{ 0, 0 }, {-1, 0 }, {-2, 0 }, {-2,-1 }}}, {{{-1, 0 }, { 0,-2 }, { 0,-1 }, { 0, 0 }}}, {{{ 0, 0 }, { 1, 0 }, { 2, 0 }, { 2, 1 }}},

        /*
         * ( 0, 2)( 1, 2)
         * ( 0, 1)
         * ( 0, 0)
         */
        /*
         * (-2, 1)             
         * (-2, 0)(-1, 0)( 0, 0)
         */
        /*
         *        ( 0, 0)
         *        ( 0,-1)
         * (-1,-2)( 0,-2) 
         */
        /*
         * ( 0, 0)( 1, 0)( 2, 0)
         *               ( 2, -1)
         */
        {{{ 0, 2 }, { 0, 1 }, { 0, 0 }, { 1, 2 }}}, {{{-2, 1 }, {-2, 0 }, {-1, 0 }, { 0, 0 }}}, {{{ 0, 0 }, { 0,-1 }, {-1,-2 }, { 0,-2 }}}, {{{ 0, 0 }, { 1, 0 }, { 2, 0 }, { 2,-1 }}},

        /*
         * ( 0, 0)
         * ( 0,-1)( 1,-1)
         *        ( 1,-2 )
         */
        /*
         *        (-1, 0)( 0, 0)
         * (-2,-1)(-1,-1)
         */

        {{{ 0, 0 }, { 0,-1 }, { 1,-1 }, { 1,-2 }}}, {{{-2,-1 }, {-1,-1 }, {-1, 0 }, { 0, 0 }}},
        /*        
         *        ( 1, 2)
         * ( 0, 1)( 1, 1)
         * ( 0, 0)
         */
        /*
         * (-2, 1)(-1, 1)
         *        (-1, 0)( 0, 0)
         */
        {{{ 0, 0 }, { 0, 1 }, { 1, 1 }, { 1, 2 }}}, {{{-2, 1 }, {-1, 1 }, {-1, 0 }, { 0, 0 }}},
        /*
         * ( 0, 0)( 1, 0)( 2, 0)
         *        ( 1,-1)
         */
        /*
         *        ( 0, 0)
         * (-1,-1)( 0,-1)
         *        ( 0,-2)
         */
        /* 
         *        (-1, 1)
         * (-2, 0)(-1, 0)( 0, 0)
         */
        /*
         * (-1, 1)
         * (-1, 0)( 0, 0)
         * (-1,-1)
         */
        {{{ 0, 0 }, { 1, 0 }, { 2, 0 }, { 1,-1 }}}, {{{ 0, 0 }, {-1,-1 }, { 0,-1 }, { 0,-2 }}}, {{{-1, 1 }, {-2, 0 }, {-1, 0 }, { 0, 0 }}}, {{{-1, 1 }, {-1, 0 }, { 0, 0 }, {-1,-1 }}}

    } 
};



class Handler {
private:
    std::vector<std::vector<int>> t;
public:
    Handler(std::vector<std::vector<int>> t): t(t) {}

    int getScoreAt(Position anker, const Polyomino tetra) const {
        int score = 0;
        for (const Position &cubic_pos: tetra.getCubicCoords()) {
            int i = cubic_pos.x + anker.x; int j = cubic_pos.y + anker.y;
            score += this->t[i][j];
        }
        return score;
    }

    bool isValid(const Polyomino &t, const Position &anker) const {
        for (const Position &p: t.coords) {
            int newx = p.x + anker.x; int newy = p.y + anker.y;
            if (this->t.size() - 1 >= newx && newx >= 0 && this->t[0].size() - 1 >= newy && newy >= 0) {
                ;
            } else return false;
        }
        return true;
    }
};

int main(void) {
    // Input Table Score (t_score)
    int N, M; std::cin >> N >> M;
    std::vector<std::vector<int>> t_score(N, std::vector<int>(M));
    for (std::size_t i = 0; i < N; ++i)
        for (std::size_t j = 0; j < M; ++j)
            std::cin >> t_score[i][j];
    Handler H(t_score); std::vector<int> score_v;

    for (const Polyomino &t: T_v) {
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < M; ++j) {
                if (H.isValid(t, Position(i, j))) {
                    score_v.push_back(H.getScoreAt(Position(i, j), t));
                }
                //print(t, Position(i, j), t_score);
            }
        }
    }
    std::cout << *std::max_element(score_v.begin(), score_v.end()) << '\n';

    return 0;
}
