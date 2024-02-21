#include <iostream>
// #include <cassert>

using namespace std;

int main (void) {
    int A, B;
    cin >> A >> B;
    // 0 < A, B < 10
    // assert(A > 0 && B < 10);
    double result = static_cast<double>(A) / static_cast<double>(B);
    cout.precision(10);
    cout << result << endl;
    return 0;
}

// TODO 자료형 변환에 대하여 정리할 것 
// TODO 자료형 별 정확도?
// TODO cout.precision은 뭘 하는 놈인가?
// HARD