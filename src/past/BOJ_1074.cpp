//https://www.acmicpc.net/problem/1074
// 2022-08-15
// BAEKJOON-STUDY

#include <iostream>
#include <cmath>

using namespace std;

int cAbstract(int N, int r, int c) {
    if (r < pow(2, N - 1)) {
        if (c < pow(2, N - 1)) {
            return 0;
        } else {
            return 1;
        }

    } else {
        if (c < pow(2, N - 1)) {
            return 2;
        } else {
            return 3;
        }
    }
}

int cArea (int N) {
    return static_cast<long int>(powl(2, 2 * N));
}

int crmap (int N, int r) {
    int new_r;
    if (r < pow(2, N - 1)) {
        new_r = r;
    } else {
        new_r = r - pow(2, N - 1);
    }
    return new_r;
}
int ccmap (int N, int c) {
    int new_c;
    if (c < pow(2, N - 1)) {
        new_c = c;
    } else {
        new_c = c - pow(2, N - 1);
    }
    return new_c;
}

int AB (int N, int r, int c) {
    if (N > 1) {
        int vpos = cAbstract(N, r, c);
        int pastCount = vpos * cArea(N - 1);
        return pastCount + AB(N - 1, crmap(N, r), ccmap(N, c));

    } else {
        return cAbstract(N, r, c);
    }
}

int main (void) {
    int N, r, c;
    cin >> N >> r >> c;
    cout << AB(N, r, c) << endl;

    return 0;
} 