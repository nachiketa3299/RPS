// * Title: 백준 16390 달리기 P3
// * Time: 17:30 19:38 (Pause)

#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>
#include <queue>
#include <map>

using namespace std;

using pos_t =  int;
constexpr pos_t kInvalidPos = -1;
template <typename t>
using _1dv = vector<t>;
template <typename t>
using _2dv = vector<vector<t>>;

using pos_off_t = int;
constexpr pos_off_t kInvalidPosOffset = -1;

struct pos2_t {
  pos_t v{kInvalidPos};
  pos_t h{kInvalidPos};
  friend pos2_t operator*(pos_off_t coeff, const pos2_t& pos) {
    return {coeff * pos.v, coeff * pos.h};
  }
  pos2_t operator+(const pos2_t& other) const {
    return {v + other.v, h + other.h};
  }
  bool operator==(const pos2_t& other) const {
    return v == other.v && h == other.h;
  }
};


class Map {
public:
  static constexpr char kPath_Char = '.';
  static constexpr char kWall_Char = '#';
  enum class State { Inv, Path , Wall };
  enum class Dir   { Inv, R, L, U, D };
  inline static map<Dir, pos2_t> off_by_dir{ \
    {Dir::R, { 0, +1}}, {Dir::L, { 0, -1}},  \
    {Dir::U, {-1,  0}}, {Dir::D, {+1,  0}}   \
  };
  struct mv_i_t {
    Dir dir{Dir::Inv};
    pos_off_t offset{kInvalidPosOffset};
  };
  using w_t = int;
  static constexpr w_t kInfiniteWeight = numeric_limits<w_t>::max();
  static constexpr w_t kInitWeight = 0;
  static constexpr int kPathFindError = -1;

  inline static pos2_t Move(const pos2_t& pivot_pos, const mv_i_t& mv_inf) {
    return pivot_pos + (mv_inf.offset * off_by_dir[mv_inf.dir]);
  }

  bool is_pos2_in_bound(const pos2_t& pos) const {
    return (0 <= pos.v && pos.v < size_v()) && (0 <= pos.h && pos.h < size_h());
  }

public:
  Map(int v_size, int h_size, int move_max) 
    : state_(v_size, _1dv<State>(h_size, State::Inv))
    , m_max_(move_max)
  {
    for (auto v = 0; v < size_v(); ++v) {
      string vline; cin >> vline;
      for (auto h = 0; h < size_h(); ++h) {
        switch (vline[h]) {
          case kPath_Char: state_[v][h] = State::Path; break;
          case kWall_Char: state_[v][h] = State::Wall; break;
          default:                                     break;
        }
      }
    }
  }
  inline int size_v() const {
    return state_.size();
  }
  inline int size_h() const {
    return state_.front().size();
  }
  bool has_wall_between(const pos2_t& s_pos2, const pos2_t& e_pos2) const {
    const auto min_v = min(s_pos2.v, e_pos2.v);
    const auto max_v = max(s_pos2.v, e_pos2.v);
    const auto min_h = min(s_pos2.h, e_pos2.h);
    const auto max_h = max(s_pos2.h, e_pos2.h);

    for (auto v = min_v; v <= max_v; ++v) {
      for (auto h = min_h; h <= max_h; ++h) {
        if (state_[v][h] == State::Wall)
          return true;
      }
    }
    return false;
  }

public:
  vector<pos2_t> AdjacentPoses(const pos2_t& pv_pos2) const {
    vector<pos2_t> ret;
    for (const auto& [dir, _dir_offset]: off_by_dir) {
      for (auto m = m_max_; m >= 1; --m) {
        const auto candid_pos2 = Move(pv_pos2, {dir, m});
        if (!is_pos2_in_bound(candid_pos2))
          continue;
        const auto &[c_v, c_h] = candid_pos2;
        if (state_[c_v][c_h] == State::Wall)
          continue;
        if (has_wall_between(pv_pos2, candid_pos2))
          break;
        ret.push_back(candid_pos2);
        break;
      }
    }
    return ret;
  }

  w_t ShortestDistance(const pos2_t& s_pos2, const pos2_t& e_pos2) {
    if (s_pos2 == e_pos2)
      return kInitWeight;

    queue<pos2_t> to_visit;
    _2dv<bool> discovered(size_v(), _1dv<bool>(size_h(), false));
    _2dv<w_t>  distances (size_v(), _1dv<w_t>(size_h(), kInfiniteWeight));

    const auto &[s_v, s_h] = s_pos2;
    to_visit.push(s_pos2);
    discovered[s_v][s_h] = true;
    distances [s_v][s_h] = kInitWeight;

    while (!to_visit.empty()) {
      const auto cv_pos2 = to_visit.front();
      const auto &[cv_v, cv_h] = cv_pos2;
      to_visit.pop();

      // if target reached?
      if (cv_pos2 == e_pos2)
        continue;


      const auto adj_pos2s = AdjacentPoses(cv_pos2);
      for (const auto& adj_pos2: adj_pos2s) {
        const auto &[a_v, a_h] = adj_pos2;
        if (discovered[a_v][a_h]) {
          distances[a_v][a_h] = min(distances[a_v][a_h], distances[cv_v][cv_h] + 1);
          continue;
        }
        // set discovered cv_pos2 ~ adj_pos2 true
        SetDiscovered(cv_pos2, adj_pos2, discovered);
        /*
        if (state_[a_v][a_h] == State::Wall)
          continue;
        */
        distances[a_v][a_h] = distances[cv_v][cv_h] + 1;
        to_visit.push(adj_pos2);
      }

    } // BFS While
    return distances[e_pos2.v][e_pos2.h];
  }
  void SetDiscovered(const pos2_t& s_pos2, const pos2_t& e_pos2, _2dv<bool>& discovered) const {
    const auto min_v = min(s_pos2.v, e_pos2.v);
    const auto max_v = max(s_pos2.v, e_pos2.v);
    const auto min_h = min(s_pos2.h, e_pos2.h);
    const auto max_h = max(s_pos2.h, e_pos2.h);
    for (auto v = min_v; v <= max_v; ++v)
      for (auto h = min_h; h <= max_h; ++h)
        discovered[v][h] = true;
  }
  void SetDistance(const pos2_t& s_pos2, const pos2_t& e_pos2, _2dv<w_t>& distances) const {
    const auto min_v = min(s_pos2.v, e_pos2.v);
    const auto max_v = max(s_pos2.v, e_pos2.v);
    const auto min_h = min(s_pos2.h, e_pos2.h);
    const auto max_h = max(s_pos2.h, e_pos2.h);
    for (auto v = min_v; v <= max_v; ++v) {
      for (auto h = min_h; h <= max_h; ++h) {
        distances[v][h];
      }
    }
  }


private:
  _2dv<State> state_;
  const int m_max_;
};

auto main() -> int {
  {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
  }

  int N, M, K;
  cin >> N >> M >> K;

  const auto& v_size  = N; // [2, 1'000]
  const auto& h_size  = M; // [2, 1'000]
  const auto& m_max   = K; // [1, 1'000]

  Map map(v_size, h_size, m_max);

  int x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;

  const auto  s_pos2  = pos2_t{--x1, --y1}; // bound [{0, 0}, {N, M})
  const auto  e_pos2  = pos2_t{--x2, --y2}; // bound [{0, 0}, {N, M})

  const auto s_dist = map.ShortestDistance(s_pos2, e_pos2);

  switch (s_dist) {
  case Map::kInfiniteWeight: cout << Map::kPathFindError; break;
  default                  : cout << s_dist;              break;
  }


  return EXIT_SUCCESS;
}