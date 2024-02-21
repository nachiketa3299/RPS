// title: 백준 2798 블랙잭 B2
// date: 14:22 15:06 38 + 6 = 44
// 보고 풀었고, 순열 조합 관련 좋은 문제.
#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>

using namespace std;

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    constexpr int kMatchCardSize = 3;
    int N; cin >> N; // [3, 100]
    int M; cin >> M; // [10, 300'000]
    vector<int> cards(N); 
    int max_sum = numeric_limits<int>::min(); // 여기에 답을 저장
    for_each(cards.begin(), cards.end(), [](auto& card){ cin >> card; });

    for (size_t i = 0    ; i < cards.size() - kMatchCardSize + 1; ++i) {
    for (size_t j = i + 1; j < cards.size() - kMatchCardSize + 2; ++j) {
    for (size_t k = j + 1; k < cards.size() - kMatchCardSize + 3; ++k) {
        const auto csum = cards[i] + cards[j] + cards[k];
        if (csum <= M)
            max_sum = max(max_sum, cards[i] + cards[j] + cards[k]);
    }}}

    cout << max_sum;

    return 0;
}