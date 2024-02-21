/*!
 * @defgroup BOJ_1074
 * 백준 1074 Z S4
 *
 * 한수는 크기가 \f$ 2^N \times 2^N \f$인 2차원 배열을 **Z** 모양으로 탐색하려고 한다.
 * 예를 들어, \f$2 \times 2\f$ 배열을 왼쪽 위칸, 오른쪽 위칸, 왼쪽 아래칸, 오른쪽 아래칸 순서로 방문하면 Z 모양이다.
 * \f$N > 1\f$인 경우, 배열을 크기가 \f$2^{N-1} \times 2^{N-1}\f$ 로 4등분 한 후, 재귀적으로 순서대로 방문한다.
 * \f$N\f$이 주어졌을 때, \f$r\f$행 \f$c\f$열은 몇 번째로 방문하는지 출력하는 프로그램을 작성한다.
 *
 * @{
 * @file 1074_231208_00.cpp
 * @date 2023-12-08
 * (12:55 ~ 13:45) (50분)
 */

#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <cmath>

#define BASE_2 2

#ifdef PS_DEBUG
#include <cassert>
#endif //PS_DEBUG

using namespace std;

/// @short 정수형 지수 계산을 위한 함수. \f$\verb|base|^\verb|p|\f$를 계산한다.
inline int Pow(int base, int p)
{
#ifdef PS_DEBUG
    assert(base > 0 && p >= 0);
#endif //PS_DEBUG

    int tbase = 1;
    if (p == 0) return tbase;
    for (size_t i = 0; i < p; ++i)
        tbase *= base;
    return tbase;
}

/*!
 * @enum EOrder
 * @short 현재 정사각형(크기가 \f$2^N \times 2^N\f$)을 한 번 자른 4개의 분할 정사각형(크기가 \f$2^{N-1} \times 2^{N-1}\f$)의 위치별 방문 순서를 나타낸다.
*/
enum EOrder 
{ 
    /// @short 왼쪽 위 분할 정사각형은 처음으로 방문한다는 뜻이다.
    TOP_LEFT=0, 
    /// @short 오른쪽 위 분할 정사각형은 두 번째로 방문한다는 뜻이다.
    TOP_RIGHT=1, 
    /// @short 왼쪽 아래 분할 정사각형은 세 번째로 방문한다는 뜻이다.
    BOTTOM_LEFT=2, 
    /// @short 오른쪽 아래 분할 정사각형은 네 번째로 방문한다는 뜻이다.
    BOTTOM_RIGHT=3 
};
inline EOrder GetRelativeVisitOrder(bool r_below_half, bool c_below_half)
{
    if (r_below_half && c_below_half)
        return TOP_LEFT;
    else if (r_below_half && !c_below_half)
        return TOP_RIGHT;
    else if (!r_below_half && c_below_half)
        return BOTTOM_LEFT;
    else if (!r_below_half && !c_below_half)
        return BOTTOM_RIGHT;
}

/*!
 * @short 재귀를 이용해 @p r 행 @p c 열이 몇 번째 순서로 방문되는지 구하는 함수
 * @param[in] N **현재 정사각형**의 한 변의 크기가 \f$2^N\f$이라는 뜻이다.
 * @param[in] r **현재 정사각형**의 행(Row) 번호이다. (*절대* 행 번호가 아니라 *상대* 행 번호이다!)
 * @param[in] c **현재 정사각형**의 열(Column) 번호이다. (*절대* 열 번호가 아니라 *상대* 열 번호이다!)
 */
int GetVisitOrder(int N, int r, int c)
{
#ifdef PS_DEBUG
    assert(N >= 1);
    assert(r >= 0 && c >= 0);
#endif //PS_DEBUG

    /// @short 현재 정사각형(한 변의 크기가 \f$2^{\verb|N|}\f$)을 한 번 4등분 했을때 나타나는 분할 정사각형들의 한 변의 길이 \f$2^{\verb|N| - 1}\f$를 나타낸다.
    const int sliced_box_size = Pow(BASE_2, N - 1);
    const bool r_below_half = (r < sliced_box_size);
    const bool c_below_half = (c < sliced_box_size);
    EOrder relative_order = GetRelativeVisitOrder(r_below_half, c_below_half);

    /*!
    * 여기서부터 재귀를 실시할지 그냥 종료할지 결정한다.
    * # 기저 사례
    * 만일 현재 탐색중인 정사각형이 크기가 \f$2^1\f$ 이면, 더 이상 분할할 수 없으므로 @p relative_order 를 반환하고 종료한다.
    * # 재귀 사례
    * 기저 사례가 아니라면,
    * @p relative_order 는 이전에 몇 개의 분할 정사각형을 지나쳐 왔는지와 값이 같다.
    * 때문에 분할 정사각형의 총 단위 사각형의 갯수(\f$\verb|sliced_box_size|^{2}\f$)에 이전에 지나쳐 온 총 분할 정사각형(@p relative_order )을 곱하면, 이제까지 지나쳐 온 총 단위 사각형의 갯수가 나온다.
    * 이제까지 지나쳐 온 것은 모두 잊고, 새로운 @p N 과 새로운 @p r , @p c 로 본 함수를 다시 호출한다.
    */
    if (N == 1) 
        return (int)relative_order;
    else
    {
        /// 새로운 행번호 @p new_r 과 새로운 행번호 @p new_c 는 분할 정사각형보다 큰지 작은지만 판단하여 크면 빼주고 아니면 그냥 쓰면 된다.
        const int new_r = (r_below_half ? r : r - sliced_box_size);
        const int new_c = (c_below_half ? c : c - sliced_box_size);

        /// 이전에 지나쳐온 총 단위 정사각형의 갯수이다.
        const int prev_unit_box_count = Pow(sliced_box_size, 2) * (int)relative_order;

        return prev_unit_box_count + GetVisitOrder(N - 1, new_r, new_c);
    }
}

int main()
{
    ///@var N
    ///@short [입력] 배열의 크기이다.
    ///@note [1, 15]
    int N; cin >> N;

    ///@var r
    ///@short [입력] 행(Row)
    ///@note [0, 2^N)
    int r; cin >> r;

    ///@var r
    ///@short [입력] 열(Column)
    ///@note [0, 2^N)
    int c; cin >> c;

    cout << GetVisitOrder(N, r, c) << '\n';

    return 0;
}

/*!
 * @}
*/
