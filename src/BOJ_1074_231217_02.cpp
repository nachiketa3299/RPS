#define PS_DEBUG

#include <iostream>
#include <cmath>

#define POW_2(X) (int)std::pow(2, X)

using namespace std;

/// @brief `r_idx`, `c_idx` 가 속한 사분면의 번호를 반환한다. 사분면은 왼쪽 위부터 Z 모양으로 0, 1, 2, 3 이다.
int GetPlane(int bsize, int r_idx, int c_idx)
{
    int n_r = r_idx / (bsize / 2);
    int n_c = c_idx / (bsize / 2);
    return 2 * n_r + n_c;
}

int GetZIndex(int bsize, int r_idx, int c_idx)
{
    if (bsize == 2)
        return GetPlane(bsize, r_idx, c_idx);

    int n_bsize = bsize / 2;
    int n_r_idx = r_idx % n_bsize;
    int n_c_idx = c_idx % n_bsize;
    int prev_bcounts = GetPlane(bsize, r_idx, c_idx) * (n_bsize * n_bsize);

    return  prev_bcounts + GetZIndex(n_bsize, n_r_idx, n_c_idx);
}

int main()
{
    int N, r, c;
    cin >> N >> r >> c;
    cout << GetZIndex(POW_2(N), r, c) << '\n';
    return 0;
}