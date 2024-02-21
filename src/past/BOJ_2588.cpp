//https://www.acmicpc.net/problem/2588

#include <iostream>
#include <cmath>

using namespace std;

int * intToArr (int);
int power (int, int);
const int MAX_SIZE = 3;

int main (void) {
    int A, B;
    // A, B length is 3 ex) 472, 385
    cin >> A;
    cin >> B;
    int * arr_B = intToArr(B);

    int result[MAX_SIZE + 1];

    for (int i = 0; i < MAX_SIZE; i++) {
        *(result + i) = A * arr_B[i];
    }
    *(result + MAX_SIZE) = A * B;

    for (int i = 0; i < MAX_SIZE + 1; i++) {
        cout << *(result + i) << endl;
    }

    return 0;
}

int power(int base, int n) {
    int p = base;
    if (n == 0) {
        return 1;
    } else if (n == 1) {
        return base;
    } else {
        for (int i = 1; i < n; i++) {
            base *= p;
        }
    }
    
    return base;
}



int * intToArr(int input) {
    // a[] = 375, a[0] = 5, a[1] = 7, a[2] = 3

    // get size of input integer ex) 300's size is 3
    int input_size;
    int temp_input = input;
    for (input_size = 1; (temp_input / 10) != 0; input_size++) {
        temp_input /= 10;
    }
    // Allocate return array
    int * int_arr = new int [input_size];

    for (int i = 0; i < input_size; i++) {
        int t = input / power(10, i);
        *(int_arr + i) = t - (t / power(10, 1)) * power(10, 1);
    }
    return int_arr;
}

// TODO int decimals 