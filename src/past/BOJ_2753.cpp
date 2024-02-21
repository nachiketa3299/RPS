#include <iostream>
#include <cassert>
using namespace std;
// 윤년은 연도가 4의 배수이면서, 100의 배수가 아닐 때 또는 400의 배수일 때이다.

bool isYYear(int year) {
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

int main (void) {
    int year;
    cin >> year;
    assert(year >= 1 && year <= 4000);

    cout << isYYear(year) << endl;
    return 0;
}