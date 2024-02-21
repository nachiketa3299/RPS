/*
https://www.acmicpc.net/problem/8393
n이 주어졌을 때, 1부터 n까지 합을 구하는 프로그램을 작성하시오.

첫째 줄에 n (1 ≤ n ≤ 10,000)이 주어진다.

1부터 n까지 합을 출력한다.

3 >> 6
*/

#include <iostream>
#include <cassert>
using namespace std;
//TODO default keyword value in C++
int sigma (int end, int start=1) {
    int sum = 0;
    for (int i = start; i <= end; i++) {
        sum += i;
    }
    return sum;
}

int main (void) {
    int n;
    cin >> n;
    assert(n >= 1 && n <= 10000);
    cout << sigma(n) << endl;
    return 0;
}