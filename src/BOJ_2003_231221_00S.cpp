// title: 
// date: 2023-12-21 22:12 22:24 (12)
#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int N; cin >> N; // [1, 1e4]
    int M; cin >> M; // [1, 3e8]
    vector<int> seq(N);
    for_each(seq.begin(), seq.end(), [](auto& e){ cin >> e; });

#ifdef PS_DEBUG
    cout << "> Input Test: ";
    for_each(seq.cbegin(), seq.cend(), [](const auto& e){ cout << e << " "; });
    cout << "\n";
#endif //PS_DEBUG

    auto sit = seq.cbegin();
    auto eit = seq.cbegin();
    auto t_sum = *sit;
    auto count = 0;

    while(sit != seq.cend())
    {
        // (1) 현재 합이 구하려는 합과 똑같음
        if (t_sum == M)
        {
#ifdef PS_DEBUG
        cout << "> Found Subseq: ";
        for_each(sit, eit + 1, [](const auto& e){ cout << e << " "; });
        cout << "\n";
#endif //PS_DEBUG
            ++count;
            if (eit + 1 == seq.cend())
                break;
            t_sum += *(++eit);
        }
        // (2) 현재 합이 더 작아서 증가시켜야함
        else if (t_sum < M)
        {
            if (eit + 1 == seq.cend())
                break;
            t_sum += *(++eit);
#ifdef PS_DEBUG
        cout << "> Moving eit: ";
        for_each(sit, eit + 1, [](const auto& e){ cout << e << " "; });
        cout << "\n";
#endif //PS_DEBUG
        }
        // (3) 현재 합이 더 커서 감소시켜야함
        else // (t_sum > M)
        {
            t_sum -= *(sit++);
#ifdef PS_DEBUG
        cout << "> Moving sit: ";
        for_each(sit, eit + 1, [](const auto& e){ cout << e << " "; });
        cout << "\n";
#endif //PS_DEBUG
        }
    }

    cout << count;

    return 0;
}