#include <iostream>
#include <algorithm>
#include <cmath>

int getTotalDigit(int n) {
    int digit = 0;

    while(n != 0) {
        n /= 10; digit++;
    }

    return digit;
}

int rev(int n) {

    int t_d = getTotalDigit(n);
    int r_n = 0;

    for (std::size_t i = 0; i < t_d; ++i) {
        int ni = n/int(pow(10,i)) - (n/int(pow(10,i+1)))*10;
        r_n += ni * pow(10, t_d - i - 1);
    }
    return r_n;
}

int main(void) {
    int A, B; std::cin >> A >> B;
    std::cout << std::max(rev(A), rev(B)) << '\n';
    return 0;
}
