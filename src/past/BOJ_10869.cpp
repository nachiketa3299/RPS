#include <iostream>

using namespace std;

int add (int, int);
int sub (int, int);
int mul (int, int);
int division (int, int);
int modo (int, int);

int main (void) {
    int A, B;
    // A & B are Natural Numbers
    cin >> A >> B;
    cout << add(A, B) << endl;
    cout << sub(A, B) << endl;
    cout << mul(A, B) << endl;
    cout << division(A, B) << endl;
    cout << modo(A, B) << endl;
    return 0;
}

int add (int A, int B) {
    return A + B;
}

int sub (int A, int B) {
    return A - B;
}

int mul (int A, int B) {
    return A * B;
}

int division (int A, int B) {
    return A / B;
}

int modo (int A, int B) {
    return A % B;
}