/*
- u_title: 백준 10813 공 바꾸기 B3
  time: 16:49 17:00
  note:
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#define PS_DEBUG
//#undef PS_DEBUG

#define PS_IO_OPT \
std::ios_base::sync_with_stdio(false);\
std::cin.tie(nullptr);\
std::cout.tie(nullptr);

using namespace std;

auto main() -> int {
    PS_IO_OPT

    int N, M; cin >> N >> M;

    // 초기 바구니에 들어있는 공 
    vector<int>        baskets(N);
    iota(baskets.begin(), baskets.end(), 1);

    // 공을 교환할 방법 입력
    struct ChangeInfo { int left{}, right{}; };
    vector<ChangeInfo> infos(M);
    for (auto& info: infos)
        cin >> info.left >> info.right;

    // 교환
    for (const auto& info: infos)    
    {
        auto it_l = baskets.begin() + (info.left - 1);
        auto it_r = baskets.begin() + (info.right - 1);
        swap(*it_l, *it_r);
    }

    for (const auto& number: baskets)
        cout << number << ' ';

    return EXIT_SUCCESS;
}