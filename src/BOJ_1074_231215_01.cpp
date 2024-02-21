// 2023-12-15 25min ÀçµµÀü

#define PS_DEBUG

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define POW_2(x) ((int)pow(2, x))
#define P_1 0
#define P_2 1
#define P_3 2
#define P_4 3

int GetPlane(int inner_size, int base_row_index, int base_column_index)
{
    const bool is_down = base_row_index < inner_size;
    const bool is_left = base_column_index < inner_size;

    if ( is_down &&  is_left) return P_1;
    if ( is_down && !is_left) return P_2;
    if (!is_down &&  is_left) return P_3;
    if (!is_down && !is_left) return P_4;

    exit(EXIT_FAILURE);
}

int GetZIndex(int size, int row_index, int column_index)
{
    if (size == 2)
    {
        return GetPlane(size / 2, row_index, column_index);
    }
    else
    {
        const int inner_size = size / 2;
        auto plane = GetPlane(inner_size, row_index, column_index);
        const int new_row_index = row_index < inner_size ? row_index : row_index - inner_size;
        const int new_column_index = column_index < inner_size ? column_index : column_index - inner_size;
        const int prev_block_counts = inner_size * inner_size * plane;
        return prev_block_counts + GetZIndex(inner_size, new_row_index, new_column_index);
    }
}

int main()
{
    int N, r, c; cin >> N >> r >> c;

    cout << GetZIndex(POW_2(N), r, c) << '\n';

    return 0;
}