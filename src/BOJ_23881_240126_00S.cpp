/*
- u_title: 백준 23881 알고리즘 수업 - 선택 정렬 1
  time: 16:04 18:02
  note:
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>

#define PS_DEBUG
//#undef PS_DEBUG
#define PS_IO_OPT std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);


using namespace std;
using e_t = int; // arr element's type

template <typename t>
using v_it_t = typename vector<t>::iterator;

struct CaptuerFunc {
  static constexpr e_t INV_ELEMENT = -1;
  CaptuerFunc(int change_count): m_change_count(change_count) {}
  bool operator()(const pair<e_t, e_t>& in) {
    m_counter++;
    if (m_counter == m_change_count) {
      const auto &[in_l, in_r] = in;
      m_ans = { min(in_l, in_r), max(in_l, in_r) };
      return true;
    }
    return false;
  }
  bool IsValid() const {
    return m_ans.first != INV_ELEMENT && m_ans.second != INV_ELEMENT;
  }
  pair<e_t, e_t> m_ans{INV_ELEMENT, INV_ELEMENT};
  const int m_change_count;
  int m_counter{0};
};

void AscSelectionSort\
  (v_it_t<e_t> fit, v_it_t<e_t> lit, CaptuerFunc& cfunc) 
{
  for (auto it = prev(lit); it != fit; it = prev(it)) {
    auto mit = max_element(fit, next(it));
    if (*it != *mit) {
      iter_swap(it, mit);
      if (cfunc({ *it, *mit }))
        return;
    }
  }
}

auto main() -> int {
  PS_IO_OPT

  int N, K;
  cin >> N >> K;
  const auto& arr_size = N;     // [5, 10'000]
  const auto& change_count = K; // [1, arr_size]
  vector<e_t> vec(N);
  for (auto& e: vec)
    cin >> e; // [1, 10^9]

  CaptuerFunc cf(change_count);
  AscSelectionSort(vec.begin(), vec.end(), cf);

  if (cf.IsValid()) {
    const auto& [l, r] = cf.m_ans;
    cout << l << ' ' << r;
  }
  else {
    cout << CaptuerFunc::INV_ELEMENT;
  }

  return EXIT_SUCCESS;
}