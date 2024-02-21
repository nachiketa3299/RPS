//https://www.acmicpc.net/problem/1052

#include <iostream>
#include <bitset>

using namespace std;
#define BS_MAX_SIZE 32
typedef bitset<BS_MAX_SIZE> Bitstream;


const int countOne (Bitstream B) {
    int count;
    for (int i = 0; i < B.size(); i++) {
        if (B[i] == 1) {
            count++;
        }
    }
    return count;
}

bool verify (Bitstream B, int K) {
    if (countOne(B) <= K) {
        return true;
    } else {
        return false;
    }
}

Bitstream increment (Bitstream B) {
    for (int i = 0; i < B.size(); i++) {
        if (B[i] == 0) {
            B[i] = 1;
            break;
        }
        B[i] = 0;
    }
    return B;
}

int main (void) {
    // Input N, K (N <= 10'000'000, K <= 1'000)
    int N, K;
    cin >> N >> K;


    const Bitstream BN (N);
    Bitstream TB (BN);

    while (!verify(TB, K)) {
        TB = increment(TB);
    }

    int answer = static_cast<int>(TB.to_ulong() - BN.to_ulong());

    return 0;
}