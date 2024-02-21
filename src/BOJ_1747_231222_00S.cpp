// title: 백준 1747 소수&팰린드롬 S1
// date: 2023-12-22 13:51 14:57 (66)
#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const vector<bool> make_prime_seq(const size_t N)
{
    vector<bool> is_prime(N + 1, true);

    is_prime[0] = false;
    is_prime[1] = false;

    for (size_t i = 2; i <= N; ++i)
    {
        if (!is_prime[i]) continue;

        for (size_t j = i + i; j <= N; j += i)
            is_prime[j] = false;
    }

    return is_prime;
}

bool is_palindrom(const int& p)
{
    string p_str = to_string(p);
    bool bis_palindrom = true;
    // 5 -> 2.5 -> 2 (0 1 / 2 / 3 4)
    for (size_t i = 0; i < p_str.size() / 2; ++i)
    {
        if (!(p_str[i] == p_str[p_str.size() - 1 - i]))
        {
            bis_palindrom = false;
            break;
        }
    }
    return bis_palindrom;
}

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int N; cin >> N; // [1, 1e6]
    int ires = 2;
    auto p_seq = make_prime_seq(ires * N);

    auto ctarget = N;

    #ifdef PS_DEBUG
    cout << "> CTarget Test: " << ctarget << "\n";
    cout << "> p_seq: ";
    for (size_t i = 0; i <= p_seq.size(); ++i)
        cout << i << "[" << boolalpha << p_seq[i] << "] ";
    cout << "\n";
    cout << "> p_seq[CTarget] Test: " << boolalpha << p_seq[ctarget] << "\n";
    cout << "\n";
    #endif //PS_DEBUG

    while(true)
    {
        for (; ctarget < p_seq.size(); ++ctarget)
        {
            const auto& bis_prime = p_seq[ctarget];

            #ifdef PS_DEBUG
            cout << "> CTarget: " << ctarget << "\n";
            if (bis_prime)      cout << "    > Prime\n";
            else                cout << "    > Not Prime\n";
            #endif //PS_DEBUG

            if (!bis_prime) continue;

            const auto bis_palindrom = is_palindrom(ctarget);

            #ifdef PS_DEBUG
            if (bis_palindrom)  cout << "    > Palindrom\n";
            else                cout << "    > Not Palindrom\n";
            #endif //PS_DEBUG

            if (!bis_palindrom) continue;

            cout << ctarget;
            return 0;
        }

        ires *= 2;
        p_seq = make_prime_seq(ires * N);

        #ifdef PS_DEBUG
        cout << ">> Resize p_seq to " << ires * N << "\n";
        #endif //PS_DEBUG
    }

    return 0;
}