/*
- u_title: 백준 10810 공 넣기 B3
  time: 16:37
  note:
*/

#include <iostream>
#include <vector>
#include <algorithm>

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
    struct Info {
        int start{}, end{};
        int number{};
    };

    vector<Info> infos(M);

    for (auto& info: infos)
        cin >> info.start >> info.end 
            >> info.number;

    vector<int> balls(N, 0);

    for (const auto& info: infos) {
        auto it_s = balls.begin() + (info.start - 1);
        auto it_e = balls.begin() + info.end;

        fill(it_s, it_e, info.number);
    }

    for (const auto& ball: balls)
        cout << ball << ' ';

    return EXIT_SUCCESS;
}