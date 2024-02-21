/*
https://www.acmicpc.net/problem/10950

두 정수 A와 B를 입력받은 다음, A+B를 출력하는 프로그램을 작성하시오.

첫째 줄에 테스트 케이스의 개수 T가 주어진다.

각 테스트 케이스는 한 줄로 이루어져 있으며, 각 줄에 A와 B가 주어진다. (0 < A, B < 10)

각 테스트 케이스마다 A+B를 출력한다.
*/

#include <iostream>
#include <cassert>

using namespace std;

int main (void) {
    int T;
    cin >> T;
    int ** Arr = new int * [T];
    for (int i = 0; i < T; i++) {
        Arr[i] = new int [2];
        cin >> Arr[i][0] >> Arr[i][1];
        assert(Arr[i][0] > 0);
        assert(Arr[i][1] < 10);
    }

    for (int i = 0; i < T; i++) {
        cout << Arr[i][0] + Arr[i][1] << endl;
    }
    return 0;
}