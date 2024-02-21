/*
- u_title: 백준 2579 계단 오르기 S3
  time: 18:12 19:58 
  note: 풀 수 있을 거 같은데...
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
  int step_count; cin >> step_count; // [1, 300]
  vector<score_t> steps(step_count);
  for (auto& step_score: steps)
    cin >> step_score;               // [1, 10'000]

  // (1) 1 or 2 step at once
  // (2) no sequential 3 steps are allowed
  // (3) last step must be stepped

  vector<score_t> ms_cache(step_count, numeric_limits<score_t>::min());

  ms_cache[0] = steps[0];

  if (step_count == 1) {
    cout << ms_cache[0];
    return EXIT_SUCCESS;
  }

  // step_count >= 2

  ms_cache[1] = max(steps[0] + steps[1], steps[1]); // logically

  if (step_count == 2) {
    cout << ms_cache[1];
    return EXIT_SUCCESS;
  }

  // step_count >= 3
  ms_cache[2] = max(steps[0] + steps[2], steps[1] + steps[2]);
  if (step_count == 3) {
    cout << ms_cache[2];
    return EXIT_SUCCESS;
  }

  // step_count >= 4

  for (size_t target_p = 3; target_p < step_count; ++target_p) {
    auto pivot_p = target_p - 3;

    /* (pivot_p) --1-> (stopover_p) --2-> (target_p) */
    const auto stopover_0_p = pivot_p + 1;
    const auto cval_0 =
      ms_cache[pivot_p]
        + steps[stopover_0_p]
        + steps[target_p];

    /* (pivot_p) --2-> (stopover_p) --1-> (target_p) */
    const auto stopover_1_p = pivot_p + 2;
    const auto cval_1 =
      ms_cache[pivot_p]
        + steps[stopover_1_p]
        + steps[target_p];
  }

  cout << ms_cache.back();

  return EXIT_SUCCESS;
}