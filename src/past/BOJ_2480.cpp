/*
https://www.acmicpc.net/problem/2480
*/

// TODO About C++ Random number generation

#include <iostream>
#include <random>

using namespace std; 

void _swap (int * arr, int a, int b) {
    int temp;
    temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
    return;
}

int max(int * arr_ptr, int size) {
    int max_index;
    int copy_arr[3];
    for (int i = 0; i < 3; i++) {
        copy_arr[i] = arr_ptr[i];
    }

    for (int uh_i = 1; uh_i < size; uh_i++) {
        for (int c = 0; c < uh_i; c++) {
            if (copy_arr[c] > copy_arr[uh_i]) {
                for (int j = uh_i; j > c; j--) {
                    _swap(copy_arr, j, j - 1);
                }
                break;
            }
        }
    }
    return copy_arr[2];

    //TODO 3 operand
}

int calculatePrize (int * arr_ptr) {
    if (arr_ptr[0] == arr_ptr[1]) {
        // 0 == 1 , 0 ? 2, 1 ? 2
        if (arr_ptr[1] == arr_ptr[2]) {
            // 0 == 1 == 2
            return 10000 + arr_ptr[1] * 1000;
        } else {
            // 0 == 1 != 2
            return 1000 + arr_ptr[0] * 100;
        }
    } else {
        // 0 != 1, 0 ? 2, 1 ? 2
        if (arr_ptr[0] == arr_ptr[2]) {
            //  0 == 2 != 1
            return 1000 + arr_ptr[0] * 100;
        } else if (arr_ptr[1] == arr_ptr[2]) {
            // 0 != 1, 0 != 2, 1 == 2
            return 1000 + arr_ptr[1] * 100;
        } else {
            // 0 != 1, 0 != 2, 1 != 2
            return max(arr_ptr, 3) * 100;
        }
    }
}

int main (void) {
    int dice_number_array[3]; 
    cin >> dice_number_array[0] >> dice_number_array[1] >> dice_number_array[2];
    cout << calculatePrize(dice_number_array) << endl;
    return 0;
}