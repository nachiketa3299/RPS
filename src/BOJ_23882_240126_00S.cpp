/*
- u_title: 백준 23882 알고리즘 수업 - 선택 정렬2
  time: 17:36 17:55 (19)
  note:
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>


#define PS_DEBUG
//#undef PS_DEBUG
#define PS_IO_OPT \
std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);

using namespace std;
using e_t = int;

template <typename t>
using v_it_t = typename vector<t>::iterator;

struct CFunc {
  static constexpr int INV_ELEMENT = -1;
  CFunc(int change_count): m_change_count(change_count) {}
  bool operator()(v_it_t<e_t> f_it, v_it_t<e_t> l_it) {
    counter++;

    if (counter != m_change_count)
      return false;

    for_each(f_it, l_it, [](const auto &e) { cout << e << " "; });
    mb_valid = true;
    return true;
  }
  bool mb_valid{false};
  const int m_change_count;
  int counter{0};
};

void AscSelectionSort \
  (v_it_t<e_t> f_it, v_it_t<e_t> l_it, CFunc& c_func) 
{
  for (auto it = prev(l_it); it != f_it; it = prev(it)) {
    auto max_it = max_element(f_it, next(it));

    if (it == max_it)
      continue;

    iter_swap(it, max_it);
    if (c_func(f_it, l_it))
      return;
  }
}

auto main() -> int {
  PS_IO_OPT

  int N, K;
  cin >> N >> K;
  const auto& arr_size = N;      // [5, 10'000]
  const auto& change_count = K;  // [1, arr_size]

  vector<e_t> vec(N);
  for (auto& e: vec)
    cin >> e;

  CFunc c_func(change_count);
  AscSelectionSort(vec.begin(), vec.end(), c_func);

  if (!c_func.mb_valid)
    cout << CFunc::INV_ELEMENT;

  return EXIT_SUCCESS;
}