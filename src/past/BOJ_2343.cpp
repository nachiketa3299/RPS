/// @file BOJ_2343.cpp
/// 백준 2343(기타 레슨, S1) https://www.acmicpc.net/problem/2343
/// 2초, 128MB
/// @date 2023-11-15T22:22

/// @details
/// 블루레이에 기타 강의 동영상을 넣으려고 한다.\n
/// - 블루레이에는 총 `N`개의 강의가 들어간다.\n
/// - 강의를 넣을 때 강의의 순서가 바뀌면 안된다.\n
/// - `i`번 강의와 `j`번 강의를 같은 블루레이에 녹화하려면, `i`와 `j` 사이의 모든 강의도 같은 블루레이에 녹화해야 한다.\n
/// 블루레이의 갯수의 `M`은 최소화 하려고 한다.
/// **블루레이의 크기(녹화 길이)도 최소로 하려고 한다.**
/// **`M` 개의 블루레이는 모두 같은 크기이다.**
/// 각 강의의 길이가 분 단위(자연수)로 주어진다.
/// **가능한 블루레이의 크기 중 최소를 구한다.**

/*! 예제 입력
9 3
2 3 4 5 6 7 8 9

*/
/*! 예제 출력
17
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

using namespace std;
using CourseCount_T = size_t;
using RayCount_T = size_t;
using Time_T = unsigned int;
using TimeVecIt_T = vector<Time_T>::iterator;

vector<Time_T> divide(TimeVecIt_T ptr_begin, TimeVecIt_T ptr_end, size_t k)
{
    static size_t recur_count = k;
    Time_T total_sum = accumulate(ptr_begin, ptr_end, 0);

    Time_T sub_sum = 0; 
    TimeVecIt_T ptr_half = ptr_begin;

    while (sub_sum < total_sum / 2)
        sub_sum += *(ptr_half++);

    /*! ptr_begin | ptr_half | ptr_end */

    TimeVecIt_T new_begin = ptr_half - ptr_begin > ptr_end - ptr_half ? 
}

int main()
{
    /// @short 블루레이 안에 들어가는 강의의 수
    CourseCount_T N; cin >> N; //< [1, 1e5]

    /// @short 블루레이의 수
    RayCount_T M; cin >> M; //< [1, N]

    /// @short N개의 강의가 길이값으로 순서대로 들어감. 순서는 유지되어야 함!
    vector<Time_T> courses(N);
    for (auto& course: courses)
        cin >> course;

    size_t k = static_cast<size_t>(log(M) / log(2));

    vector<Time_T> course_chunk = divide(course_chunk.begin(), course_chunk.end() - 1, k);

    return 0;
}

