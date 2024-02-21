#include <iostream>
#include <vector>

#define CM_EAST 1
#define CM_WEST 2
#define CM_NORT 3
#define CM_SOUT 4

using namespace std;

typedef struct {
    int _x;
    int _y;
} Position2D;

class Map {
private:
    int m_width;
    int m_height;
    vector<vector<int>> m_inf;
public: /* Constructor */
    Map (int N, int M, vector<vector<int>> map_inf)
        : m_width(M), m_height(N) {
        this->m_inf = map_inf;
    }

public: /* General Functions */
    bool isInWBoundary (int coord) {
        return (coord >= 0 && coord < this->m_width);
    }
    bool isInHBoundary (int coord) {
        return (coord >= 0 && coord < this->m_height);
    }

public: /* Getters */
    int getWidth (void) {
        return this->m_width;
    }
    int getHeight (void) {
        return this->m_height;
    }
    int getInf (Position2D pos) {
        return this->m_inf[pos._x][pos._y];
    }

public: /* Setters */
    void setInf (Position2D pos, int i) {
        this->m_inf[pos._x][pos._y] = i;
        return;
    }
public: /* For debug purpose */
    void print(void) {
        cout << "==Map start==" << endl;
        for (auto infs: this->m_inf) {
            for (auto inf: infs) {
                cout << inf << " ";
            }
            cout << endl;
        }
        cout << "==Map end==" << endl;
        return;
    }
};

class Dice {
private:
    typedef struct {
        int _bottom;
        int _top;
        int _east;
        int _west;
        int _north;
        int _south;
    } Pip;
private:
    Pip m_pip;
    Position2D m_pos;
public: /* Constructor */
    Dice (Position2D pos) : m_pos(pos) {
        this->m_pip = Pip { 1, 6, 3, 4, 2, 5 };
        return;
    }
public:
    vector<int> bulkRollDiceSave (Map &map, vector<int> cms) {
        vector<int> result;
        for (int c: cms) {
            if (this->_rollDiceSave(map, c)) {
                result.push_back(this->getTop());
            }
        }
        return result;
    }
    const int getTop (void) {
        return this->m_pip._top;
    }
private:
    Dice &_changeBottom (int v) {
        this->m_pip._bottom = v;
        return *this;
    }
    bool _rollDiceSave (Map &map, int c) {
        cout << "Before Rolling" << endl;
        this->print();
        map.print();
        if (this->_rollDice(map, c)) {
            if (map.getInf(this->m_pos) == 0) {
                map.setInf(this->m_pos, this->m_pip._bottom);
            } else {
                this->_changeBottom(map.getInf(this->m_pos));
                map.setInf(this->m_pos, 0);
            }
            cout << "After Rolling(Rolled)" << endl;
            this->print();
            map.print();
            return true;
        }
        return false;
    }
    bool _rollDice (Map map, int c) {
        Pip t_pip = this->m_pip;
        switch (c) {
            case CM_EAST:
                if (map.isInWBoundary(this->m_pos._x + 1)) {
                    this->m_pip._bottom = t_pip._east;
                    this->m_pip._east   = t_pip._top;
                    this->m_pip._top    = t_pip._west;
                    this->m_pip._west   = t_pip._bottom;

                    this->m_pos._x += 1;
                    return true;
                }
                break;
            case CM_WEST:
                if (map.isInWBoundary(this->m_pos._x - 1)) {
                    this->m_pip._bottom = t_pip._west;
                    this->m_pip._east   = t_pip._bottom;
                    this->m_pip._top    = t_pip._east;
                    this->m_pip._west   = t_pip._top;

                    this->m_pos._x -= 1;
                    return true;
                }
                break;
            case CM_NORT:
                if (map.isInHBoundary(this->m_pos._y + 1)) {
                    this->m_pip._bottom = t_pip._north;
                    this->m_pip._north  = t_pip._top;
                    this->m_pip._top    = t_pip._south;
                    this->m_pip._south  = t_pip._bottom;

                    this->m_pos._y += 1;
                    return true;
                }
                break;
            case CM_SOUT:
                if (map.isInHBoundary(this->m_pos._y - 1)) {
                    this->m_pip._bottom = t_pip._south;
                    this->m_pip._north  = t_pip._bottom;
                    this->m_pip._top    = t_pip._north;
                    this->m_pip._south  = t_pip._top;

                    this->m_pos._y -= 1;
                    return true;
                }
                break;
        }
        return false;
    }
public:
    void print (void) {
        cout << "==Dice start==" << endl;
        cout << "Pos (" << this->m_pos._x << ", " << this->m_pos._y << ")" << endl;
        cout << "X " << this->m_pip._north << " X" << endl;
        cout << this->m_pip._west << " ";
        cout << this->m_pip._bottom << " ";
        cout << this->m_pip._east << " " << endl;;
        cout << "X " << this->m_pip._south << " X" << endl;
        cout << "X " << this->m_pip._top << " X" << endl;
        cout << "==Dice end==" << endl;
        return;
    }
};


int main (void) {
    // Input first line
    int N, M, x, y, n_cm;
    cin >> N >> M >> x >> y >> n_cm;

    Dice dice (Position2D { x, y });
    cout << endl;
    cout << "First State of Dice" << endl;
    dice.print();


    // Input map infos and save to vector map_inf
    vector<vector<int>> map_inf (N, vector<int>(M));
    for (vector<int> &n: map_inf) {
        for (int &m: n) {
            cin >> m;
        }
    }

    // Initialize map
    Map map (N, M, map_inf);
    cout << "First state of Map" << endl;
    map.print();

    // Input commands and save to vector cms(commands)
    vector<int> cms (n_cm);
    for (int &cm: cms) {
        cin >> cm;
    }

    // Process
    // dice.bulkRollDiceSave results the vector of result top pips.
    vector<int> top_result = dice.bulkRollDiceSave(map, cms);

    // Output results
    for (auto t: top_result) {
        cout << t << endl;
    }

    return 0;
}
