// https://www.acmicpc.net/problem/4673
// `[2022-08-17T22:34, ]`

#include <iostream>
#define BOUND 10'000

using namespace std;

int sumDigit (int n) {
    // sum each digit of number ex) 23 -> 2 + 3 = 5
    int sum = 0;
    while (n != 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int genNextNonSelfNum (int n) {
    return n + sumDigit(n);
}

int main (void) {
    vector<bool> main_arr(BOUND, false);
    return 0;
}