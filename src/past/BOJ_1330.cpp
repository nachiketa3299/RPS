#include <iostream>
#include <cassert>

using namespace std;

int main (void) {
    int A, B;
    cin >> A >> B;

    assert(A >= -10000 && B >= -10000);
    assert(A <= 10000 && B <= 10000);

    if (A > B) {
        cout << ">" << endl;
    } else if (A < B) {
        cout << "<" << endl;
    } else if (A == B) {
        cout << "==" << endl;
    }

    return 0;
}