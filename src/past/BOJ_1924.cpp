// https://www.acmicpc.net/problem/1924
// BAEKJOON-STUDY

#include <iostream>
#include <string>
#define BASE_MONTH 1
#define BASE_DAY 1

using namespace std;

class Calendar {
private:
    const int y = 2007;
    int month;
    int day;
    int fullday;
public:
    Calendar (int m, int d)
        :month(m), day(d)  {
        const int m_l_d[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int full_month_days = 0;
        for (int i = BASE_MONTH; i < this->month; i++) {
            full_month_days += m_l_d[i - 1];
        }
        this->fullday = full_month_days + this->day - BASE_DAY;
        return;
    }
    const string getDow (void) {
        const string dow_list[7] = {
            "MON"
            , "TUE"
            , "WED"
            , "THU"
            , "FRI"
            , "SAT"
            , "SUN"
        };
        return dow_list[this->fullday % 7];
    }
};

int main (void) {
    int x, y;
    cin >> x >> y;
    Calendar today (x, y);

    cout << today.getDow() << endl;
    return 0;
}