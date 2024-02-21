// * Title: ¹éÁØ 1600 ¸»ÀÌ µÇ°íÇÂ ¿ø¼þÀÌ G3
// * Time: 16:50 17:50

#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <utility>
#include <queue>

using namespace std;

struct Pos2_t {
public:
  using Pos_t = int;
  static constexpr Pos_t kInvalidPos = 0;
public:
  static vector<Pos2_t> Get_RLUD_Offsets() {
    return { { -1, 0 }, { +1, 0 }, { 0, -1 }, { 0, +1 } };
  }
  static vector<Pos2_t> Get_Knight_Offsets() {
    return { 
      { -2, -1 }, { -2, +1 },
      { +2, -1 }, { +2, +1 },
      { -1, -2 }, { -1, +2 },
      { +1, +2 }, { +1, -2 }
    };
  }
static vector<Pos2_t> GetOffsets() {
  const auto offset_rlud = Get_RLUD_Offsets();
  const auto offset_knight = Get_Knight_Offsets();
  vector<Pos2_t> offsets;
  offsets.insert(offsets.end(), offset_rlud.begin(), offset_rlud.end());
  offsets.insert(offsets.end(), offset_knight.begin(), offset_knight.end());
  return offsets;
}
Pos2_t operator+(const Pos2_t& other) const {
  return { v + other.v, h + other.h };
}
inline bool is_v_in_bound(Pos_t min_bound, Pos_t max_bound) const {
  return min_bound <= v && v < max_bound;
}
inline bool is_h_in_bound(Pos_t min_bound, Pos_t max_bound) const {
  return min_bound <= h && h < max_bound;
}
Pos_t v = kInvalidPos;
Pos_t h = kInvalidPos;
};

class BGraph {
public:
  using Pos_t = Pos2_t::Pos_t;
  using Weight_t = int;
  static constexpr Weight_t kInfiniteWeight = numeric_limits<Weight_t>::max();
  static constexpr Weight_t kZeroWeight = 0;
  static constexpr int kPathFindError = -1;
private:
  enum class State {
    Invalid = -1, Path = 0, Wall = 1
  };
  friend istream& operator>>(istream& is, State& state) {
    int state_int;
    is >> state_int;
    state = static_cast<State>(state_int);
    return is;
  }

public:
  BGraph(size_t v_size, size_t h_size, size_t move_limit)
    : board_(v_size, vector<State>(h_size, State::Invalid))
    , mv_limit_(move_limit)
  { 
    for (auto v = 0; v < size_v(); ++v)
      for (auto h = 0; h < size_h(); ++h)
        cin >> board_[v][h];
  }
  inline size_t size_v() const {
    return board_.size();
  }
  inline size_t size_h() const {
    return board_.front().size();
  }
  vector<Pos2_t> FindAdjacentPoses(const Pos2_t& cv_pos) {
    vector<Pos2_t> ret;
    for (const auto& offset: Pos2_t::GetOffsets()) {
      const auto candid_pos = cv_pos + offset;
      if (!(0 <= candid_pos.v && candid_pos.v < size_v()))
        continue;
      if (!(0 <= candid_pos.h && candid_pos.h < size_h()))
        continue;
      ret.push_back(candid_pos);
    }
    return ret;
  }
  vector<Pos2_t> FindAdjacent_RLUD_Poses(const Pos2_t& cv_pos) {
    vector<Pos2_t> ret;
    for (const auto& offset: Pos2_t::Get_RLUD_Offsets()) {
      const auto c_pos = cv_pos + offset;
      if (!c_pos.is_v_in_bound(0, size_v()))
        continue;
      if (!c_pos.is_h_in_bound(0, size_h()))
        continue;
      ret.push_back(c_pos);
    }
    return ret;
  }
  vector<Pos2_t> FindAdjacent_Knight_Poses(const Pos2_t& cv_pos) {
    vector<Pos2_t> ret;
    for (const auto& offset: Pos2_t::Get_Knight_Offsets()) {
      const auto c_pos = cv_pos + offset;
      if (!c_pos.is_v_in_bound(0, size_v()))
        continue;
      if (!c_pos.is_h_in_bound(0, size_h()))
        continue;
      ret.push_back(c_pos);
    }
    return ret;
  }
  Weight_t BFS_ShortestPath(const Pos2_t& s_pos, const Pos2_t& e_pos) {
    using g_pair = pair<Pos2_t, int>; // pos, move_count

    queue<g_pair> to_visit;
    vector<vector<vector<Weight_t>>> dist_by_mv_cnts(mv_limit_ + 1,            \
      vector<vector<Weight_t>>(size_v(),                                       \
        vector<Weight_t>(size_h(), kInfiniteWeight)));
    vector<vector<vector<bool>>> discovered(mv_limit_ + 1,                     \
      vector<vector<bool>>(size_v(),                                           \
        vector<bool>(size_h(), false)));

    auto init_mv_cnt = 0;
    dist_by_mv_cnts[init_mv_cnt][s_pos.v][s_pos.h] = kZeroWeight;
    discovered[init_mv_cnt][s_pos.v][s_pos.h] = true;
    to_visit.push({ s_pos, init_mv_cnt });

    while (!to_visit.empty()) {
      const auto [cv_pos, cv_mv_cnt] = to_visit.front();
      to_visit.pop();

      for (const auto& adj_pos: FindAdjacent_RLUD_Poses(cv_pos)) {
        const auto& new_mv_cnt = cv_mv_cnt;
        if (discovered[new_mv_cnt][adj_pos.v][adj_pos.h])
          continue;
        discovered[new_mv_cnt][adj_pos.v][adj_pos.h] = true;

        const auto& adj_state = board_[adj_pos.v][adj_pos.h];

        switch(adj_state) {
          case State::Path:
            dist_by_mv_cnts[new_mv_cnt][adj_pos.v][adj_pos.h] =                \
              dist_by_mv_cnts[cv_mv_cnt][cv_pos.v][cv_pos.h] + 1;
            to_visit.push({ adj_pos, new_mv_cnt });
            break;
          default:
          case State::Wall:
            break;
        }
      }

      for (const auto& adj_pos: FindAdjacent_Knight_Poses(cv_pos)) {
        const auto& new_mv_cnt = cv_mv_cnt + 1;
        if (!(new_mv_cnt <= mv_limit_))
          continue;
        if (discovered[new_mv_cnt][adj_pos.v][adj_pos.h]) 
          continue;
        discovered[new_mv_cnt][adj_pos.v][adj_pos.h] = true;

        const auto& adj_state = board_[adj_pos.v][adj_pos.h];
        switch(adj_state) {
          case State::Path:
            to_visit.push({ adj_pos, new_mv_cnt });
            dist_by_mv_cnts[new_mv_cnt][adj_pos.v][adj_pos.h] =                \
              dist_by_mv_cnts[cv_mv_cnt][cv_pos.v][cv_pos.h] + 1;
            break;
          default:
          case State::Wall:
            break;
        }
      }
    }

    vector<int> epos_mv_cnts;
    for (auto mv_cnt = 0; mv_cnt <= mv_limit_; mv_cnt++)
      epos_mv_cnts.push_back(dist_by_mv_cnts[mv_cnt][e_pos.v][e_pos.h]);

    return *min_element(epos_mv_cnts.cbegin(), epos_mv_cnts.cend());
  }

private:
  vector<vector<State>> board_;
  size_t mv_limit_;
};

auto main() -> int
{
  {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
  }
  int K, W, H;
  cin >> K;
  cin >> W >> H;
  const auto& move_limit = K;
  const auto& board_v_size = H;
  const auto& board_h_size = W;

  BGraph b(H, W, K);
  const auto dist = b.BFS_ShortestPath(Pos2_t{0, 0}, Pos2_t{H-1, W-1});
  switch(dist) {
    case BGraph::kInfiniteWeight:
      cout << BGraph::kPathFindError;
      break;
    default:
      cout << dist;
      break;
  }
  return EXIT_SUCCESS;
}