// https://www.acmicpc.net/problem/1712
// 2022-08-13T04:31 ~ T04:48

#include <iostream>

using namespace std;

int findBEV (int fc,  int vp,  int p) {
    int per_net_benefit = p - vp;
    if (per_net_benefit <= 0) {
        return -1;
    } else {
        int noi = 0;
        while (per_net_benefit * noi - fc <= 0)  {
            noi++;
        }
        return noi;
    }
}


int main (void) {
    // Fixed Cost A = FC
    // Variable Cost B = VP
    // Noteboook Price C = P

    int FC, VP, P;
    cin >> FC >> VP >> P;

    cout << findBEV(FC, VP, P) << endl;

    return 0;
}