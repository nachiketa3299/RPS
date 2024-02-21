/* 
https://www.acmicpc.net/problem/2741

자연수 N이 주어졌을 때, 1부터 N까지 한 줄에 하나씩 출력하는 프로그램을 작성하시오.

첫째 줄에 100,000보다 작거나 같은 자연수 N이 주어진다.

첫째 줄부터 N번째 줄 까지 차례대로 출력한다.

5

>>

1
2
3
4
5
*/

#include <iostream>
#include <cassert>
using namespace std;
// TODO ios_base 는 using namespace 가 왜 안되는거야
int main (void) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    assert(N >= 1 && N <= 100'000);
    for (int i = 0; i < N; i++) {
        cout << i + 1 << '\n';
    }
    return 0;
}