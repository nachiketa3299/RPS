#include <iostream>
#include <cassert>
using namespace std;

bool isInRange(int target, int min, int max) {
    return target >= min && target <= max;
}

int main (void) {
    int score;
    cin >> score;
    assert(score >= 0 && score <= 100);

    if (isInRange(score, 90, 100)) {
        cout << "A" << endl;
    } else if (isInRange(score, 80, 89)) {
        cout << "B" << endl;
    } else if (isInRange(score, 70, 79)) {
        cout << "C" << endl;
    } else if (isInRange(score, 60, 69)) {
        cout << "D" << endl;
    } else {
        cout << "F" << endl;
    }
    return 0;
}
