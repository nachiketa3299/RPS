#include <iostream>
#include <cassert>

using namespace std;

int whatQuadrant(int x, int y) {
    int quadrant_index = 0;

    assert(x > 0 || x < 0);
    assert(y > 0 || y < 0);
    assert(x <= 1000 && x >= -1000);
    assert(y <= 1000 && y >= -1000);
    assert(x != 0);
    assert(y != 0);

    if (x > 0 && y > 0) {
        quadrant_index = 1;
    } else if (x > 0 && y < 0) {
        quadrant_index = 4;
    } else if (x < 0 && y > 0) {
        quadrant_index = 2;
    } else if (x < 0 && y < 0) {
        quadrant_index = 3;
    }

    return quadrant_index;
}

int main (void) {
    int x, y;
    cin >> x >> y;
    cout << whatQuadrant(x, y) << endl;
    return 0;
}