/*!
* @file BOJ_1021_231205.cpp
* @date 2023-12-05T18:03
* 백준 1021 회전하는 큐 S3
*/

/*!
* 지민이는 N개의 원소를 포함하고 있는 양방향 순환 큐를 가지고 있다.
* 지민이는 이 큐에서 몇 개의 원소를 뽑아내려고 한다.
* 지민이는 이 큐에서 다음과 같은 3가지 연산을 수행할 수 있다.
* - (1) 원소를 뽑아내기
* - (2) 왼쪽으로 한 칸 이동시키기
* - (3) 오른쪽으로 한 칸 이동시키기
* 큐에 처음에 포함되어 있던 수 N이 주어진다.
* 지민이가 뽑아내려는 원소의 위치가 주어진다. (가장 처음의 큐 위치)
* 그 원소를 주어진 순서대로 뽑아내는데 드는 2, 3번 연산의 최솟값을 출력하는 프로그램을 작성한다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

int main()
{
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr); std::cout.tie(nullptr);
    }

    /// @short 원형 큐의 크기 
    /// @note [1, 50]
    size_t N; cin >> N;
    /// @short 원형 큐에서 뽑아내려고 하는 수의 갯수
    /// @note M <= N 인 자연수
    size_t M; cin >> M;

    deque<int> dq;
    for (size_t i = 1; i <= N; ++i)
        dq.push_back(i);


    return 0;
}