// https://www.acmicpc.net/problem/2231
// 2022-08-22
// - `[2022-08-22T12:00, 2022-08-22T12:08]`

#include <iostream>

using namespace std;

int calSumDecom (const int input) {
    int i_t = input;
    int digit_sum = 0;
    while (i_t != 0) {
        digit_sum += i_t % 10;
        i_t /= 10;
    
    return input + digit_sum;
}

int main (void) {
    int N; 
    cin >> N;

    int smallest_gen = 0;
    for (int i = 1; i < N; i++) {
        if (calSumDecom(i) == N) {
            smallest_gen = i;
            break;
        }
    }

    cout << smallest_gen << endl;
    return 0;
}

