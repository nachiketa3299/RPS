/// @date 2023-11-16T15:16
/// 백준 10816(숫자 카드 2, S4)

/// 숫자 카드는 정수 하나가 적혀져 있는 카드이다.
/// 숫자 카드 `N` 개를 가지고 있다.
/// 정수 `M` 개가 주어졌을 때, 이 수가 적혀있는 숫자 카드를 상근이가 몇 개 가지고 있는지 구하는 프로그램을 작성한다.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using Count_T = unsigned int;
using Integer_T = int;
using IntegerVIT_T = vector<Integer_T>::iterator;

int main()
{
    Count_T N; cin >> N; //< [1, 5e5]

    vector<Integer_T> cards(N);
    for (Integer_T& card : cards) cin >> card;


    sort(cards.begin(), cards.end());

    Count_T M; cin >> M; //< [1, 5e5]

    vector<Integer_T> targets(M);
    for (Integer_T& target : targets) cin >> target;

    for (Integer_T& target : targets)
    {
        auto range = equal_range(cards.begin(), cards.end(), target);
        Count_T cnt = distance(range.first, range.second);
        cout << cnt << ' ';
    }


    return 0;
}