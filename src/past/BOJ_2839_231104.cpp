/// @date 2023-11-04
/// 백준 2839 설탕 배달 https://www.acmicpc.net/problem/2839
/// Dynamic Programming, Greedy Algorithm

#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;
#define INVALID -1

int main()
{
    array<int, 2> kbags { 3, 5 }; sort(kbags.begin(), kbags.end(), less<int>());
    const auto& kbag_max = kbags.back();
    const auto& kbag_min = kbags.front();

    int N; cin >> N; ///< [1, 5e3]

    /// 캐시 초기화
    vector<int> bags(N >= kbag_max ? N + 1 : kbag_max + 1, INVALID);
    for (const auto& kbag: kbags) 
        bags[kbag] = 1;
    /// Tabulation until N
    for (int i = kbag_max + 1; i <= N; ++i)
    {
        vector<int> candid;
        for (const auto& kbag : kbags)
            /// @short `i` kg을 봉지로 나누는 법은 이전에 계산한 `i - 봉지크기` kg을 봉지에 나누는 법 중에서 가장 작은 것에 +1을 한 것
            if (bags[i - kbag] != INVALID) candid.push_back(bags[i - kbag]);
        if (candid.empty())
        {
            bags[i] = INVALID;
            continue;
        }
        bags[i] = *min_element(candid.begin(), candid.end()) + 1;
    }
    cout << bags[N] << '\n';
    return 0;
}