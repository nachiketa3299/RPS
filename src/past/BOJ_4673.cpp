// https://www.acmicpc.net/problem/4673
// 2022-08-10

#include <iostream>

using namespace std;
const int SIZE = 10000;

int sumDigit (int n) {
    int sum = 0;
    int next_add; 

    while (n != 0) {
        next_add = n % 10;
        sum += next_add;
        n /= 10;
    }

    return sum;
}

int eGenerator (int n) {
    return n + sumDigit(n);
}
void initMainArray(int * arr, const int SIZE){
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1;
    }
    return;
}
// TODO 배열을 함수에 포인터로 전달했을때, 크기를 같이 전달하지 않아도 &e를 쓰면 되는가?

// TODO 배열의 크기를 넘겨주는 더 우아한 방법?
// TODO Mark As Hard
// TODO You can do this with bool array and its index! 

void printNonZero (int * arr, int SIZE) {
    for (int i = 0; i < SIZE; i++) {
        if (arr[i] != 0) {
            cout << arr[i] << endl;
        }
    }
}

int main (void) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    // Initialize main array
    int main_arr[SIZE];
    initMainArray(main_arr, SIZE);

    for (int g = 0; g < SIZE + 1; g++) {
        if (main_arr[g] != 0) {
            int generated_element = eGenerator(g + 1);
            while(generated_element <= SIZE) {
                main_arr[generated_element - 1] = 0; // Discard element marked as 0
                generated_element = eGenerator(generated_element);
            }
        }
    }

    printNonZero(main_arr, SIZE);

    return 0;
}