/*
https://www.acmicpc.net/problem/10818

N개의 정수가 주어진다. 이때, 최솟값과 최댓값을 구하는 프로그램을 작성하시오.

첫째 줄에 정수의 개수 N (1 ≤ N ≤ 1,000,000)이 주어진다. 둘째 줄에는 N개의 정수를 공백으로 구분해서 주어진다. 모든 정수는 -1,000,000보다 크거나 같고, 1,000,000보다 작거나 같은 정수이다.

첫째 줄에 주어진 정수 N개의 최솟값과 최댓값을 공백으로 구분해 출력한다.

5
20 10 35 30 7
>>
7 35
*/

#include <iostream>
// TODO Time Complexity Sort Algorithm

using namespace std;

int * insertionSort (int * arr, int size) {
    int * arr_ptr = new int [size];
    for (int i = 0; i < size; i++) {
        arr_ptr[i] = arr[i];
    }
    for (int uhi = 1; uhi < size; uhi++) {
        for (int ci = 0; ci < uhi; ci++) {
            if (arr_ptr[uhi] < arr_ptr[ci]) {
                for (int i = uhi; i > ci; i--) {
                    int temp = arr_ptr[i - 1];
                    arr_ptr[i - 1] = arr_ptr[i];
                    arr_ptr[i] = temp;
                }
                break;
            }
        }
    }
    return arr_ptr;
}

int main (void) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N;
    int * arr_ptr;
    cin >> N;
    arr_ptr = new int [N];
    for (int i = 0; i < N; i++) {
        cin >> arr_ptr[i];
    }

    int * sorted_arr = insertionSort(arr_ptr, N);
    cout << sorted_arr[0] << " " << sorted_arr[N - 1] << endl;

    delete [] arr_ptr;
    delete [] sorted_arr;

    return 0;
}
