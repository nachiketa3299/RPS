/*
- u_title: 코딩은 체육과목 입니다.
  time: 16:26
  note:
*/

#include <iostream>
#include <string>

#define PS_DEBUG
//#undef PS_DEBUG

#define PS_IO_OPT \
std::ios_base::sync_with_stdio(false);\
std::cin.tie(nullptr);\
std::cout.tie(nullptr);

using namespace std;
const string long_string = "long ";

auto main() -> int {
    PS_IO_OPT

    int N; cin >> N; // [4, 1000], N = 4k (k = 1, 2, 3, ...)
    static auto LongCount = [](const int& N) { return N / 4; };
    for (int i = 0; i < LongCount(N); ++i)
        cout << long_string;
    cout << "int";

    return EXIT_SUCCESS;
}