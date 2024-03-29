/*
- u_title: 백준 2579 계단 오르기 S3
  time: 12:47
  note: 
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

#define PS_DEBUG
//#undef PS_DEBUG

#define PS_IO_OPT \
std::ios_base::sync_with_stdio(false);\
std::cin.tie(nullptr);\
std::cout.tie(nullptr);

using namespace std;
using score_t = int;

auto main() -> int {
  PS_IO_OPT

  int step_count;
  cin >> step_count;

  constexpr score_t MIN_SCORE = numeric_limits<score_t>::min();

  vector<score_t> steps(step_count);
  for (auto& step: steps)
    cin >> step; // [1, 10'000]
  
  /*
  [--] [  ] [0 ] [  ] [1 ] [  ] [2 ] [  ] [3 ] [  ] [4 ] [  ] [5 ]
  [--] [  ] [10] [  ] [20] [  ] [15] [  ] [25] [  ] [10] [  ] [20]
    |********>|-------->|-------->|-------->|-------->|-------->   [ X ]
    |********>|==================>|-------->|-------->|-------->   [ X ]
    |********>|-------->|-------->|==================>|-------->   [ O ]
            [10]      [30]      [45]                [55]      [75]
    |********>|==================>|==================>|-------->   [ X ]
    |********>|-------->|==================>|-------->|-------->   [ O ]
            [10]      [30]                [55]      [65]      [85]
    |********>|-------->|-------->|-------->|==================>   [ X ]
    |********>|-------->|==================>|==================>   [ O ]
            [10]      [30]                [55]                [75]
    |******************>|-------->|-------->|-------->|-------->   [ X ]
    |******************>|==================>|-------->|-------->   [ O ]
                      [20]                [45]      [55]      [75]
    |******************>|-------->|==================>|-------->   [ O ]
                      [20]      [35]                [45]      [65]
    |******************>|-------->|-------->|==================>   [ O ]
                      [20]      [35]      [60]                [80]
    |******************>|==================>|==================>   [ O ]
                      [20]                [45]                [65]
----------------------------------------------------------------------
            [10]      [30]
  */

  vector<score_t> max_score(step_count, MIN_SCORE);

  return EXIT_SUCCESS;
}