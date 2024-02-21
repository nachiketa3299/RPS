//https://www.acmicpc.net/problem/15596
// 2022-08-10
// TODO C++ For Each Loop
// TODO C++ Reference (&)
// TODO C++ Vector Library Basic Usages
//      - https://hwan-shell.tistory.com/119

#include <iostream>
#include <vector>

using namespace std;

typedef long long LongInt;
typedef vector<int> IntVector;

LongInt sumN (const IntVector &vec) {
    LongInt sum = 0;
    for (const int &e: vec) {
        sum += e;
    }
    return sum;
}

int main (void) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N;
    cin >> N;

    IntVector vec(N);
    for (int i = 0; i < N; i++) {
        cin >> vec[i];
    }

    cout << sumN(vec) << '\n';

    return 0;
}