// title: 백준 27866 문자와 문자열 B5
// date: 1
#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <string>

using namespace std;

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }
    string S; cin >> S;
    size_t i; cin >> i;
    cout << S[i - 1];

    return 0;
}