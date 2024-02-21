// * Title: 백준 13415 정렬 게임
// * Time: 11:57 12:21 포기 어려워! 갈피못잡겠음
// * Note: 

#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

auto main() -> int
{
  {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
  }

  int N; cin >> N;
  const auto& seq_count = N; // [1, 100'000]

  vector<int> seq(seq_count);
  static const auto input = [](auto& e){cin >> e; return e;};
  transform(seq.begin(), seq.end(), seq.begin(), input);
  // [1, A] asc, [1, B] dsc
  // indexify
  // if A >  B then  3 2 1 4
  // if A == B then [1, B] dsc
  // if A <  B then [1, B] dsc

  int K; cin >> K;
  const auto& set_count = K; // [1, 100'000]
  vector<pair<int, int>> sets(set_count); // A_pos B_pos
  static const auto p_input = [](auto& e) -> pair<int, int> { 
    auto& [a_e_pos, b_e_pos] = e;
    cin >> a_e_pos >> b_e_pos; return e;
  };
  transform(sets.begin(), sets.end(), sets.begin(), p_input);

  return EXIT_SUCCESS;
}