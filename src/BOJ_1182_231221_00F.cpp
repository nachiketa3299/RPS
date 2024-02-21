// title: ���� 1182 �κ� ������ �� S2
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

    // ũ�Ⱑ ����� �κм��� �߿��� �� ������ ���Ҹ� �� ���� ���� S�� �Ǵ� ����� ���� ���Ѵ�.

    vector<int> btree_subsum((size_t)pow(2, N), 0);

    #define L_Child
    #define R_Child
    populate_btree(seq, 0, btree_subsum);

    return 0;
}