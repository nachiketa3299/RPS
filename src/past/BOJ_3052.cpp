/*
https://www.acmicpc.net/problem/3052
두 자연수 A와 B가 있을 때, A%B는 A를 B로 나눈 나머지 이다. 예를 들어, 7, 14, 27, 38을 3으로 나눈 나머지는 1, 2, 0, 2이다. 

수 10개를 입력받은 뒤, 이를 42로 나눈 나머지를 구한다. 그 다음 서로 다른 값이 몇 개 있는지 출력하는 프로그램을 작성하시오.

첫째 줄부터 열번째 줄 까지 숫자가 한 줄에 하나씩 주어진다. 이 숫자는 1,000보다 작거나 같고, 음이 아닌 정수이다.

첫째 줄에, 42로 나누었을 때, 서로 다른 나머지가 몇 개 있는지 출력한다.

1
2
3
4
5
6
7
8
9
10
>>
10
*/

#include <iostream>

using namespace std;

const int DIVIDER = 42;
const int INPUT_NUM = 10;

void input (int * arr, int size) {
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }
    return;
}

void  fillDiv (int * div, int * arr, int size, int divider) {
    for (int i = 0; i < size; i++) {
        div[i] = arr[i] % divider;
    }
    return;
}
void fillDivExist (int * div_arr, bool * div_exist, int size) {
    for (int i = 0; i < size; i++) {
        if (!div_exist[div_arr[i]]) {
            div_exist[div_arr[i]] = true;
        }
    }
    return;
}
int calDivNum (bool * div_exist, int divider_size) {
    int result = 0;
    for (int i = 0; i < divider_size; i++) {
        if (div_exist[i]) {
            result++;
        }
    }
    return result;
}

int main (void)  {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int input_arr [INPUT_NUM];
    input (input_arr,  INPUT_NUM);

    int div_arr [INPUT_NUM];
    fillDiv(div_arr, input_arr, INPUT_NUM, DIVIDER);

    bool div_exist [DIVIDER]; // 0 -> 1
    for  (int i = 0; i < DIVIDER; i++) {
        div_exist[i] = false;
    }

    fillDivExist(div_arr, div_exist, INPUT_NUM);

    int result = calDivNum(div_exist, DIVIDER);
    cout << result << '\n';
    return 0;
}