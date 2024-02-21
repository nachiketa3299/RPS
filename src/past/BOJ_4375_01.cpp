#include <iostream>
#include <cmath>


long long int makeOneNum(int n) {
    long long int one_num = 0;
    const int base = 10;
    for (std::size_t i = 0; i < n; ++i) {
        one_num += int(pow(base, i));
    }
    return one_num;
}

int getDigit(long long int n) {
    int digit = 0;
    for (std::size_t d = 1; ; d *= 10) {
        if (n / d != 0)  digit++;
        else break;
    }
    return digit;
}

// m(2) = 10 * m(1) + m(1) = 11
// m(3) = 10 * m(2) + m(2) = 10(11) + 1
// gd(123) 
/// 1111 = m(4) 

int main(void) {
    while(true) {
        int n; std::cin >> n;
        if (std::cin.eof()) break;
        else {
            int c_digit = getDigit(n);
            long long int cand;
            for (int c_digit = getDigit(n) + 1;;++c_digit) {
                cand = makeOneNum(c_digit + 1);
                if (cand % n == 0) break;
            }
            std::cout << getDigit(cand) << '\n';
        }
    }
    return 0;
}
