// title: 백준 1182 부분 수열의 합 S2
// date: 2023-12-22 T 15:39
#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void populate_btree(const vector<int>& seq, size_t sidx, vector<int>& btree)
{
    if (sidx == 0)
    {
        btree[sidx] = seq[sidx];
    }
    else
    {
        if (sidx < seq.size())
        {
            populate_btree
        }
    }
}

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int N; cin >> N; // [1, 20]
    int S; cin >> S; // [-1e6, 1e6]
    vector<int> seq(N, 0);
    for_each(seq.begin(), seq.end(), [](auto& e) { cin >> e; });

    #ifdef PS_DEBUG
    cout << "> Input seq: ";
    for_each(seq.cbegin(), seq.cend(), [](const auto& e) { cout << e << " "; });
    #endif //PS_DEBUG 

    // 크기가 양수인 부분수열 중에서 그 수열의 원소를 다 더한 값이 S가 되는 경우의 수를 구한다.

    vector<int> btree_subsum((size_t)pow(2, N), 0);

    #define L_Child
    #define R_Child
    populate_btree(seq, 0, btree_subsum);

    return 0;
}