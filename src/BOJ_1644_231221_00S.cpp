// title: 백준 1644 소수의 연속합 G3
// date:  2023-12-21 22:27 22:50 (23)
#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> make_prime_seq_until(int N)
{
    vector<int> ret;
    if (N == 1) 
        return ret;
    vector<bool> is_prime(N + 1, true);

    is_prime[0] = false;
    is_prime[1] = false;

    for (size_t i = 2; i <= N; ++i)
    {
        if (!is_prime[i]) continue;

        for (size_t j = i + i; j <= N; j += i)
            is_prime[j] = false;
    }
    for (size_t i = 2; i < is_prime.size(); ++i)
        if (is_prime[i]) ret.push_back(i);
    return ret;
}

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int N; cin >> N; // [1, 4e6]
    const auto p_seq = make_prime_seq_until(N);

    #ifdef PS_DEBUG
    cout << "> Input Test N: " << N << "\n";
    cout << "> Prime Seq: ";
    for_each(p_seq.cbegin(), p_seq.cend(), [](const auto& e) {cout << e << " "; });
    cout << '\n';
    #endif //PS_DEBUG

    if (p_seq.size() == 0)
    {
        cout << "0";
        return 0;
    }

    auto sit = p_seq.cbegin();
    auto eit = p_seq.cbegin();
    auto count = 0;
    auto t_sum = *sit;

    while (sit != p_seq.cend())
    {
        if (t_sum == N)
        {
            ++count;
            if (eit + 1 == p_seq.cend()) break;
            t_sum += *(++eit);
        }
        else if (t_sum < N)
        {
            if (eit + 1 == p_seq.cend()) break;
            t_sum += *(++eit);
        }
        else // (t_sum > N)
        {
            t_sum -= *(sit++);
        }
    }
    cout << count;

    return 0;
}