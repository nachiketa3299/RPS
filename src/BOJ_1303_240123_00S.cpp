/*
* Title: 백준 1303 전투 S1 
* Time: 22:21 10:54 (33)
*/

#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <numeric>

using namespace std;

class WarZone {
public:
  enum class TeamColor { Invalid = -1, Blue, White };
  using pos_t = int;
  static constexpr pos_t kInvalidPos = -1;
  struct pos2_t {
    static vector<pos2_t> GetOffsets() {
      return { { -1, 0 }, { +1, 0 }, { 0, -1 }, { 0, +1 } };
    }
    pos2_t operator+(const pos2_t& other) const {
      return { v + other.v, h + other.h };
    }
    inline bool is_in_v_bound(size_t min_bound, size_t max_bound) const {
      return min_bound <= v && v < max_bound;
    }
    inline bool is_in_h_bound(size_t min_bound, size_t max_bound) const {
      return min_bound <= h && h < max_bound;
    }

    pos_t v { kInvalidPos };
    pos_t h { kInvalidPos };
  };
  WarZone(size_t v_size, size_t h_size)
    : warzone_(v_size, vector<TeamColor>()) 
  {
    for (auto v = 0; v < v_size; ++v) {
      string input_line; cin >> input_line;
      for (const auto& c: input_line) {
        switch (c) {
          case 'W': warzone_[v].push_back(TeamColor::White); break;
          case 'B': warzone_[v].push_back(TeamColor::Blue); break;
          default : warzone_[v].push_back(TeamColor::Invalid); break;
        }
      }
    }
  }
  inline size_t size_v() const {
    return warzone_.size();
  }
  inline size_t size_h() const {
    return warzone_.front().size();
  }
  vector<pos2_t> FindAdjacentPoses(pos2_t cv_pos) const {
    vector<pos2_t> ret;
    for (const auto& offset: pos2_t::GetOffsets()) {
      const auto c_pos = cv_pos + offset;
      if(!(c_pos.is_in_v_bound(0, size_v())))
        continue;
      if(!(c_pos.is_in_h_bound(0, size_h())))
        continue;
      ret.push_back(c_pos);
    }
    return ret;
  }

  pair<int, int> CalculatePowers() const {
    vector<int> b_powers;
    vector<int> w_powers;

    static vector<vector<bool>> discovered(size_v(), vector<bool>(size_h(), false));

    for (auto v = 0; v < size_v(); ++v) {
      for (auto h = 0; h < size_h(); ++h) {
        if (discovered[v][h])
          continue;

        const pos2_t init_pos { v, h };
        queue<pos2_t> to_visit;
        const auto& init_color = warzone_[v][h];
        auto size = 0;
        
        to_visit.push(init_pos);
        discovered[init_pos.v][init_pos.h] = true;

        while (!to_visit.empty()) {
          const auto cv_pos = to_visit.front();
          to_visit.pop();

          (++size);

          for (const auto& adj_pos: FindAdjacentPoses(cv_pos)) {
            if (discovered[adj_pos.v][adj_pos.h])
              continue;

            const auto& adj_color = warzone_[adj_pos.v][adj_pos.h];
            if (!(init_color == adj_color))
              continue;

            discovered[adj_pos.v][adj_pos.h] = true;
            to_visit.push(adj_pos);
          }
        }

        if (size == 0)
          continue;

        switch(init_color) {
          case TeamColor::White: w_powers.push_back(size * size); break;
          case TeamColor::Blue : b_powers.push_back(size * size); break;
        }

      }
    }

    const auto my_power = accumulate(w_powers.cbegin(), w_powers.cend(), 0);
    const auto en_power = accumulate(b_powers.cbegin(), b_powers.cend(), 0);
    return { my_power, en_power };
  }

private:
  vector<vector<TeamColor>> warzone_;
};

auto main() -> int
{
  {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
  }

  int N, M; cin >> N >> M;

  const auto& v_size = M; // [1, 100]
  const auto& h_size = N; // [1, 100]

  WarZone wz(v_size, h_size);
  const auto [my_power, en_power] = wz.CalculatePowers();
  cout << my_power << ' ' << en_power;


  return EXIT_SUCCESS;
}