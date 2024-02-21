// 2022-08-24
// https://www.acmicpc.net/problem/2839
#include <iostream>

using namespace std;

const int calMinContainer (const int N) {
    const int con_max_5 = N / 5;

    for (int i = con_max_5; i >= 0; i--)  {
        const int mod_5 = N - (i * 5);
        const int mod_3 = mod_5 % 3;

        if (mod_3 == 0) {
            const int con_3 = mod_5 / 3;
            return i + con_3;
        } else {
            // Nothing
        }
    }

    return -1;
}

int main (void) {

    // (3 <= N <= 5000)
    int N;
    cin >> N; 
    cout << calMinContainer(N) << endl;


    return 0;
}