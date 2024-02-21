/// @date 2023-11-16T15:00
/// 백준 1920(수 찾기, S4)
/// 128MB, 1초

/// `N` 개의 정수 `A[1]`, `A[2]`, ..., `A[N]`이 주어질 때, 이 안에 `X`라는 정수가 존재하는지 알아내는 프로그램을 작성한다.

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

using NaturalNumber_T = unsigned int;
using IntegerNumber_T = int;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    NaturalNumber_T N; cin >> N; ///< [1, 1e5]
    vector<IntegerNumber_T> to_find(N);
    for (auto& v : to_find) cin >> v;
    sort(to_find.begin(), to_find.end());
    NaturalNumber_T M; cin >> M; ///< [1, 1e5]
    vector<IntegerNumber_T> targets(M);
    for (auto& v : targets) cin >> v;

    for (auto& target : targets)
    {
        cout << binary_search(to_find.begin(), to_find.end(), target) << '\n';
    }

    return 0;
}
