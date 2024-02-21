// * Title: 백준 2206 벽 부수고 이동하기 G3
// * Time: 15:15 16:41 (86)
// * Note: Input 관련해서 조심 하셈!

#define PS_DEBUG
// #undef PS_DEBUG

#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using pos_t = int;
constexpr pos_t kInvalidPos = -1;
struct pos2_t {
  pos2_t operator+(const pos2_t &other) const {
    return {v + other.v, h + other.h};
  }
  bool operator==(const pos2_t &other) const {
    return v == other.v && h == other.h;
  }
  pos_t v{kInvalidPos};
  pos_t h{kInvalidPos};
};

class Map {
  inline static const vector<pos2_t> offsets{{-1, 0}, {+1, 0}, {0, -1}, {0, +1}};
  enum State {
    Invalide = -1,
    Path = 0,
    Wall = 1
  };

public:
  Map(int v_size, int h_size)
      : state_(v_size, _1dv<State>(h_size, State::Invalide)) {
    for (auto v = 0; v < size_v(); ++v) {
      string state_str;
      cin >> state_str;
      for (auto h = 0; h < size_h(); ++h) {
        switch (state_str[h]) {
        default:
          break;
        case '0':
          state_[v][h] = State::Path;
          break;
        case '1':
          state_[v][h] = State::Wall;
          break;
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
  inline bool is_pos2_in_bound(const pos2_t &pos) const {
    return (0 <= pos.v && pos.v < size_v()) && (0 <= pos.h && pos.h < size_h());
  }
  vector<pos2_t> AdjacentPoses(const pos2_t &pivot_pos) const {
    vector<pos2_t> ret;
    for (const auto &offset : offsets) {
      const auto candid_pos = pivot_pos + offset;
      if (!is_pos2_in_bound(candid_pos))
        continue;
      ret.push_back(candid_pos);
    }
    return ret;
  }

public:
  using weight_t = int;
  static constexpr weight_t kInfiniteWeight = numeric_limits<weight_t>::max();
  static constexpr weight_t kInitWeight = 1;
  static constexpr int kPathFindError = -1;
  template <typename T>
  using _2dv = vector<vector<T>>;
  template <typename T>
  using _1dv = vector<T>;
  static constexpr int kMaxBreakCount = 1;

  weight_t ShortestPathDistance(const pos2_t &s_pos2, const pos2_t &e_pos2) const {
    const struct b_pair {
      int bc{0}; // break_count
      pos2_t pos2;
    } i_pair{0, s_pos2};
    const auto &[i_bc, i_pos2] = i_pair;
    const auto &[i_v, i_h] = i_pos2;

    queue<b_pair> to_visit;
    array<_2dv<weight_t>, kMaxBreakCount + 1> distances;
    { // Init distances(INF)
      fill(distances.begin(), distances.end(),
           _2dv<weight_t>(size_v(), _1dv<weight_t>(size_h(), kInfiniteWeight)));
    }
    array<_2dv<bool>, kMaxBreakCount + 1> discovered;
    { // Init discovered(false)
      fill(discovered.begin(), discovered.end(),
           _2dv<bool>(size_v(), _1dv<bool>(size_h(), false)));
    }

    // Initalize BFS
    to_visit.push(i_pair);
    distances[i_bc][i_v][i_h] = kInitWeight;
    discovered[i_bc][i_v][i_h] = true;

    // Conduct BFS
    while (!to_visit.empty()) {
      const auto [cv_bc, cv_pos2] = to_visit.front();
      const auto &[cv_v, cv_h] = cv_pos2;

      // If target reached? (If reached, it must be shortest distance cuz BFS)
      if (cv_pos2 == e_pos2) {
        _1dv<weight_t> candid_s_distances;
        for (auto bc = 0; bc < kMaxBreakCount + 1; ++bc)
          candid_s_distances.push_back(distances[bc][cv_v][cv_h]);
        const auto min_s_distance =
            *min_element(candid_s_distances.cbegin(), candid_s_distances.cend());
        return min_s_distance;
      }

      to_visit.pop();

      const auto adj_pos2s = AdjacentPoses(cv_pos2);
      const auto a_bc = cv_bc;

      // (case 1) Does not break wall
      for (const auto &adj_pos2 : adj_pos2s) {
        const auto &[a_v, a_h] = adj_pos2;

        if (discovered[a_bc][a_v][a_h])
          continue;
        if (state_[a_v][a_h] == State::Wall)
          continue;

        discovered[a_bc][a_v][a_h] = true;
        distances[a_bc][a_v][a_h] = distances[cv_bc][cv_v][cv_h] + 1;
        to_visit.push({a_bc, adj_pos2});
      }

      const auto a_nbc = cv_bc + 1;
      if (!(a_nbc <= kMaxBreakCount))
        continue;

      // (case 2) Does break wall
      for (const auto &adj_pos2 : adj_pos2s) {
        const auto &[a_v, a_h] = adj_pos2;

        if (discovered[a_nbc][a_v][a_h])
          continue;
        if (state_[a_v][a_h] == State::Path)
          continue;

        discovered[a_nbc][a_v][a_h] = true;
        distances[a_nbc][a_v][a_h] = distances[cv_bc][cv_v][cv_h] + 1;
        to_visit.push({a_nbc, adj_pos2});
      }
    } // BFS While
    return kInfiniteWeight;
  }

private:
  _2dv<State> state_;
};

auto main() -> int {
  {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
  }

  int N, M;
  cin >> N >> M;
  const auto &v_size = N; // [1, 1'000]
  const auto &h_size = M; // [1, 1'000]

  const pos2_t s_pos2{0, 0};
  const pos2_t e_pos2{N - 1, M - 1};

  Map map(v_size, h_size);

  const auto s_dist = map.ShortestPathDistance(s_pos2, e_pos2);
  switch (s_dist) {
  case Map::kInfiniteWeight:
    cout << Map::kPathFindError;
    break;
  default:
    cout << s_dist;
    break;
  }

  return EXIT_SUCCESS;
}