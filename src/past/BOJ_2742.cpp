/*
https://www.acmicpc.net/problem/2742

자연수 N이 주어졌을 때, N부터 1까지 한 줄에 하나씩 출력하는 프로그램을 작성하시오.

첫째 줄에 100,000보다 작거나 같은 자연수 N이 주어진다.

첫째 줄부터 N번째 줄 까지 차례대로 출력한다.

*/

#include <iostream>
#include <cassert>

using namespace std;

int main (void) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;
    assert(T >= 1 && T <= 100'000);

    for (int i = 0; i < T; i++) {
        cout << T - i << '\n';
    }

    return 0;
}