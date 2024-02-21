// * Title: 백준 6603 로또 S2
// * Time: 21:29 22:02
/*
 * Note:
 * `next_permutation` 사용이 익숙하지 않다.
 * bitset을 사용해 보려고 했으나 템플릿 클래스라서 동적으로 만들 수가 없다.
 * dynamic_bitset 은 boost 라이브러리에 있다고 한다.
*/

#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;
constexpr int kLotteryNumberCount = 6;

vector<int> operator*(const vector<int>& origin, const vector<int>& mask) {
  vector<int> ret;
  for (auto i = 0; i < origin.size(); ++i) {
    if (!(mask[i] == 0))
      continue;
    ret.push_back(origin[i]);
  }
  return ret;
}
// [TODO) fuck 

auto main() -> int
{
  {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
  }

  constexpr int kInputEnd = 0;
  auto input = [](auto& e) { cin >> e; return e; };

  while (true) {
    // -- Test Case Starts --
    int k; cin >> k; // (6, 13)

    if (k == kInputEnd)
      break;

    vector<int> S(k); // Ascending order
    transform(S.begin(), S.end(), S.begin(), input);

    vector<int> comb_mask(k, 1);
    fill_n(comb_mask.begin(), kLotteryNumberCount, 0);

    do {
      const auto l_seq = S * comb_mask;
      for_each(l_seq.cbegin(), l_seq.cend(), [](const auto& e) { cout << e << ' '; });
      cout << '\n';
    } while (next_permutation(comb_mask.begin(), comb_mask.end()));
    cout << '\n';

  } // -- Test Case Ends -- 

  return EXIT_SUCCESS;
}