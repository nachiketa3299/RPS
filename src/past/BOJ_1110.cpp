/*
https://www.acmicpc.net/problem/1110

0보다 크거나 같고, 99보다 작거나 같은 정수가 주어질 때 다음과 같은 연산을 할 수 있다. 먼저 주어진 수가 10보다 작다면 앞에 0을 붙여 두 자리 수로 만들고, 각 자리의 숫자를 더한다. 그 다음, 주어진 수의 가장 오른쪽 자리 수와 앞에서 구한 합의 가장 오른쪽 자리 수를 이어 붙이면 새로운 수를 만들 수 있다. 다음 예를 보자.
26부터 시작한다. 2+6 = 8이다. 새로운 수는 68이다. 6+8 = 14이다. 새로운 수는 84이다. 8+4 = 12이다. 새로운 수는 42이다. 4+2 = 6이다. 새로운 수는 26이다.
위의 예는 4번만에 원래 수로 돌아올 수 있다. 따라서 26의 사이클의 길이는 4이다.
N이 주어졌을 때, N의 사이클의 길이를 구하는 프로그램을 작성하시오.
첫째 줄에 N이 주어진다. N은 0보다 크거나 같고, 99보다 작거나 같은 정수이다.
첫째 줄에 N의 사이클 길이를 출력한다.

26 >> 4
*/

#include <iostream>

using namespace std;

int digit_arr [2];

int * _digitize (int N, int * digit_arr) {
    for (int i = 0; i < 2; i++) {
        digit_arr[i]  = N % 10;
        N /= 10;
    }
    return digit_arr;
}

int _makeNewNum (int N) {

    int digit_sum = _digitize(N, digit_arr)[1] + _digitize(N, digit_arr)[0];
    int first = (digit_sum >= 10) ? (digit_sum % 10) : (digit_sum);
    int result = _digitize(N, digit_arr)[0] * 10 + first; 

    return result;
}

int cycleReps (int N) {
    int cycle_reps = 1;
    int new_N = N;
    while (_makeNewNum(new_N) != N) {
        cycle_reps++;
        new_N = _makeNewNum(new_N);
    }
    return cycle_reps;
}

int main (void) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    cout << cycleReps(N) << '\n';

    return 0;
}