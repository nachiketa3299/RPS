#include <iostream>
#include <cassert>

using namespace std;

int toSyear (int);

int main (void) {
    int byear;
    cin >> byear;
    assert(byear >= 1000 && byear <= 3000);

    cout << toSyear(byear) << endl;
    return 0;
}

int toSyear (int byear) {
    return byear - 543;
}