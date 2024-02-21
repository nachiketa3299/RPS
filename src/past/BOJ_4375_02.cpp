#include <iostream>
#include <cmath>

int getDigit(int n) {
    int digit = 0;
    for (std::size_t d = 1; ; d *= 10) {
        if (n / d != 0) digit++;
        else break;
    }
    return digit;
}

long long int makeOneNum(int digit) {
    long long int one_num = 0;
    const int base = 10;
    for (std::size_t i = 0; i < digit; ++i) {
        one_num += int(pow(base, i));
    }
    return one_num;
}

int main(void) {
    while (true) {
        int n; std::cin >> n;
        if (std::cin.eof()) break;
        else {
            int cur_n_digit = getDigit(n);
            long long int cand = makeOneNum(cur_n_digit);
            std::size_t t_one_num_digit = cur_n_digit;
            for(; cand % n != 0; ++t_one_num_digit) {
                cand = 10 * (cand % n) + 1;
            }
            std::cout << t_one_num_digit << '\n';
        }
    }
    return 0;
}

// cand  = n * K  + R  (0 <= R < n) , cand is one_num
// cand % n = R
// cand' = n * K' + R'
// 10 * cand + 1 = 10 * (n * K) + 10 * R + 1
// 10 * R + 1이 n의 배수면 된다. 
// 그러므로 다음 판단은 10 * R + 1 % n == 0
// 그런데 R = cand % n
// 따라서 cand' = 10(cand % n) + 1
