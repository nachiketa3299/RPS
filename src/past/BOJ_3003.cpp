// 2022-08-23
//https://www.acmicpc.net/problem/3003

#include <iostream>

using namespace std;

#define CHESS_SIZE 6

enum Chess {
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    NIGHT,
    PAWN,
};

int main (void) {
    int chess_num [CHESS_SIZE];
    chess_num[KING] = 1;
    chess_num[QUEEN] = 1;
    chess_num[ROOK] = 2;
    chess_num[BISHOP] = 2;
    chess_num[NIGHT] = 2;
    chess_num[PAWN] = 8;

    int input_arr [CHESS_SIZE];

    for (int i = 0; i < CHESS_SIZE; i++) {
        cin >> input_arr[i];
    }

    int output_arr [CHESS_SIZE];
    for (int i = 0; i < CHESS_SIZE; i++) {
        output_arr[i] = chess_num[i] - input_arr[i];
    }

    for (auto e: output_arr) {
        cout << e << " ";
    }

    return 0;
}

//TODO https://boycoding.tistory.com/179