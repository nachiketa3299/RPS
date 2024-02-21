#include <iostream>
#include <vector>

using namespace std;


typedef struct {
    int _x, _y, _z;
} Position3D;

typedef struct {
} RipeDirection3D;

class TomatoCell {
private:
    RipeDirection3D m_near;
    int m_ripe_state;
public: /* Constructor */
    TomatoCell (int ripe_state)
        : m_ripe_state(ripe_state) {}
};

typedef vector<vector<vector<TomatoCell>>> TGrid3D;

class Box {
private:
    Position3D m_hnm;
    TGrid3D m_grid;
    bool m_can_be_all_riped;
    bool m_is_all_riped;
public: /* Constructor */
    Box (Position3D hnm) : m_hnm(hnm) {}
public: /* General Functions */
    void put (TomatoCell t, Position3D pos) {
        this->m_grid[pos._z][pos._y][pos._x] = t;
        return;
    }
    void init (void) {
        this->_calCanBeAllRiped ();
        if (this->canBeAllRiped()) {
            this->_initTomato();
        } 
        return;
    }
    void ripe (void) {
        return;
    }
public: /* Getter */
    bool canBeAllRiped (void) {
        return this->m_can_be_all_riped;
    }
    bool isAllRiped (void) {
        for (auto n: this->m_grid) {
            for (auto m: n) {
                for (auto t: m) {
if
                }
            }
        }
        return this->m_is_all_riped;
    }
private:
    void _calCanBeAllRiped (void) {
        return;
    }
    void _initTomato (void) {
        return;
    }
};




int main (void) {
    int M, N, H;
    cin >> M >> N >> H;
    Box box (Position3D { H, N, M });

    for (int h = 0; h < H; h++) {
        for (int n = 0; n < N; n++) {
            for (int m = 0; m < M; m++) {
                int ripe_state;
                cin >> ripe_state;
                TomatoCell tomato (ripe_state);
                box.put(tomato, Position3D { h, n, m });
            }
        }
    }

    box.init();
    int days;
    if (box.canBeAllRiped()) {
        days = 0;
        while (box.isAllRiped()) {
            box.ripe();
            days++;
        }
    } else {
        days = -1;
    }

    cout << days << endl;

    return 0;
}
