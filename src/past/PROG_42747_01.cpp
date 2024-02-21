/*!
* @date 2023.10.29
* 어떤 과학자가 발표한 논문 `n`편 중, `h`번 이상 인용된 논문이 `h`편 이상이고, 나머지 논문 `h`번 이하 인용되었다면 `h`의 최댓값이 이 과학자의 H-Index이다.
* 어떤 과학자가 발표한 논문의 인용 횟수를 담은 배열 `citations`가 매개변수로 주어질 때, 이 과학자의 H-Index를 반환하도록 `solution` 함수를 작성한다.
* - 과학자가 발표한 논문의 수 `n`은 [1, 1e3]이다.
* - 논문별 인용 횟수는 [0, 1e4]이다.
*/

#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> citations)
{
    int answer = 0;

    int max_h = 0;
    sort(citations.begin(), citations.end(), less<int>());

    for (size_t p_idx = 0; p_idx < citations.size() - 1; ++p_idx)
    {
        int h = citations[p_idx]; //< p_idx 번 논문의 인용 횟수
        int p_geq_h = p_idx + 1;

        if (h - 1 > citations[p_idx + 1])
        {
            h--;
            p_geq_h++;
        }
        if (h <= p_geq_h)
        {
            max_h = h;
            break;
        }
    }

    answer = max_h;

    return answer;
}

#include "PGS.h"


int main(void)
{
    Solver<vector<int>, int> sol
    {
        {
            { {3, 0, 6, 1, 5}, 3 },
            { {0, 5, 6, 7, 8}, 4 }
        }
    }; 
    sol();
}

