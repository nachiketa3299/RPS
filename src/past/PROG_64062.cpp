#include "PROG.h"

/// @file PROG_64062.cpp
/// @date 2023-11-16T22:36 - 2023-11-17T24:23 (FAIL)
/// 프로그래머스 64062 (징검다리 건너기, 2)
/// https://school.programmers.co.kr/learn/courses/30/lessons/64062

/// <징검다리를 건너는 규칙>
/// (1) 징검다리는 일렬로 놓여 있고, 각 징검다리의 디딤돌에는 모두 숫자가 적혀 있으며, 디딤돌의 숫자는 한 번 밟을 때마다 1씩 줄어든다.
/// (2) 디딤돌의 숫자가 0이 되면 더 이상 밟을 수 없으며, 이때는 그 다음 디딤돌로 한번에 여러 칸 건너 뛸 수 있다.
/// (3) 단, 다음으로 밟을 수 있는 디딤돌이 여러개인 경우, 무조건 가까운 디딤돌로만 건너 뛸 수 있다.

/// <니니즈 친구들이 징검다리를 건너는 규칙>
/// (1) 니니즈 친구들은 개울의 왼쪽에 있고, 개울의 오른쪽 건너편에 도착해야 징검다리를 건넌 것으로 인정한다.
/// (2) 니니즈 친구들은 한 번에 한 명씩 징검다리를 건너며, 한 명이 징검다리를 모두 건넌 후, 그 다음 친구가 건너기 시작한다.

/// 디딤돌에 적힌 숫자가 순서대로 담긴 배열 `stones`와 한 번에 건너뛸 수 있는 디딤돌의 최대 칸 수 `k`가 매개변수로 주어질 때, 최대 몇 명까지 징검다리를 건널 수 있는지 반환하도록 `solution` 함수를 완성한다.

/*!
* <제한 사항>
* - 징검다리를 건너야 하는 니니즈 친구들의 수는 무제한이라고 간주한다.
* - `stones` 배열의 크기는 [1, 2e5]이다.
* - `stones` 배열 각 원소의 값은 [1, 2e8]인 자연수이다.
* - `k` 는 [1, `stones.size()`] 이다.
*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using StoneHP_T = int;
using Count_T = int;
using WindowIt_T = vector<StoneHP_T>::iterator;

int solution(vector<StoneHP_T> stones, Count_T k)
{
    Count_T min_niniz_cnt;

    auto win_start = stones.begin();
    auto win_end = win_start + k - 1;

    Count_T niniz_cnt = *max_element(win_start, win_end);
    min_niniz_cnt = niniz_cnt;


    while (win_end + 1 != stones.end())
    {
        auto& to_pop_front = *(win_start);
        auto& to_push_back = *(win_end + 1);

        if (to_push_back > niniz_cnt)
        {

            win_start++;
            win_end++;
            continue;
        }
        else
        {
            niniz_cnt = *max_element(win_start + 1, win_end + 1);
            if (niniz_cnt < min_niniz_cnt) 
                min_niniz_cnt = niniz_cnt;
            win_start++;
            win_end++;
        }

    }


    return min_niniz_cnt;
}



int main()
{
    vector<int> vec = { 2, 4, 5, 3, 2, 1, 4, 2, 5, 1 };
    int k = 3;
    cout << solution(vec, 3);
    return 0;
}
