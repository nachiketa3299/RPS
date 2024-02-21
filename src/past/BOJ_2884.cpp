#include <iostream>
#include <cassert>

using namespace std;
// TODO 구조체 선언에 대해서 

typedef struct Clock {
    int H;
    int M;
} Clock;

Clock * getNewAlarm (const Clock * c_i, const int min) {
    Clock * c_o = new Clock;
    if (c_i->M > min) {
        c_o->H = c_i->H;
        c_o->M = c_i->M - min;
    } else {
        int left_hour = c_i->H - 1;
        if (left_hour >= 0) {
            c_o->H = left_hour;
        } else {
            c_o->H = left_hour + 24;
        }
        c_o->M = c_i->M + 60 - min;
    }
    return c_o;
}

int main (void) {

    Clock * c_i = new Clock;
    cin >> c_i->H >> c_i->M;

    assert(c_i->H >= 0 && c_i->H <= 23);
    assert(c_i->M >= 0 && c_i->M <= 59);

    Clock * c_o = getNewAlarm(c_i, 45);
    cout << c_o->H << " " << c_o->M << endl;

    delete c_i;
    delete c_o;

    return 0;
}
