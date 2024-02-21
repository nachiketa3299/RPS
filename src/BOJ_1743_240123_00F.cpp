// * Title: 백준 1743 음식물 피하기
// * Time: 60
// * note: 도대체 왜 안되는 거지?

#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>

using namespace std;

class HallWay {
public:
  using pos_t = int;
  static constexpr pos_t kInvalidPos = -1;

public:
  enum class State { Empty, Garbage };

public: // Just position 2D POD simple sub struct
  struct pos2_t {
    pos2_t operator+(const pos2_t& other) const {
      return { v + other.v, h + other.h };
    }
  public:
    pos_t v { kInvalidPos };
    pos_t h { kInvalidPos };
  };

public:
// offset for meaning "adjacent"
inline static const vector<pos2_t> offsets { {-1, 0}, {+1, 0}, {0, -1}, {0, +1} };

public: // Constructor
  HallWay(size_t v_size, size_t h_size, size_t g_count) 
    : state_(v_size, vector<State>(h_size, State::Empty))
  {
    // Input in here
    for (size_t i = 0; i < g_count; ++i) {
      int v, h; cin >> v >> h;
      state_[--v][--h] = State::Garbage;
    }
  }
public: // 
  inline size_t size_v() const {
    return state_.size();
  }
  inline size_t size_h() const {
    return state_.front().size();
  }
  inline bool is_pos2_in_bound(const pos2_t& cv_pos) const {
    return (0 <= cv_pos.v && cv_pos.h < size_v()) && \
      (0 <= cv_pos.h && cv_pos.h < size_h());
  }

public:
  vector<pos2_t> FindAdjacentPoses(const pos2_t& cv_pos) const {
    vector<pos2_t> ret;
    for (const auto& offset: HallWay::offsets) {
      const auto c_pos = cv_pos + offset;
      if (!is_pos2_in_bound(c_pos))
        continue;
      ret.push_back(c_pos);
    }
    return ret;
  }

public:
  // ** Use DFS to Search all State::Garbage nodes
  size_t CalConnectedComponentMaxSize() const {
    size_t max_size = numeric_limits<size_t>::min();
    vector<vector<bool>> visited(size_v(), vector<bool>(size_h(), false));

    for (size_t v = 0; v < size_v(); ++v) {
      for (size_t h = 0; h < size_h(); ++h) {
        if (visited[v][h])
          continue;

        if (state_[v][h] == State::Empty) {
          visited[v][h] = true;
          continue;
        }

        // ↓ for all not visited, not empty(garbage) nodes
        // proceed dfs

        size_t size = 0;
        const pos2_t init_pos { (int)v, (int)h };
        DFS_Recur(init_pos, visited, size);
        max_size = max(max_size, size);
      }
    }

    return max_size;
    /* BFS takes lot of memory...
    for (auto v = 0; v < size_v(); ++v) {
      for (auto h = 0; h < size_h(); ++h) {
        if (discovered[v][h])
          continue;
        const auto& init_state = hallway_[v][h];
        if (init_state == State::Empty)
          continue;

        const auto init_pos = pos2_t{ v, h };
        queue<pos2_t> to_visit;
        to_visit.push(init_pos);
        discovered[init_pos.v][init_pos.h] = true;
        size_t size = 0;

        while (!to_visit.empty()) {
          const auto cv_pos = to_visit.front();
          to_visit.pop();

          (++size);

          for (const auto& adj_pos: FindAdjacentPoses(cv_pos)) {
            if (discovered[adj_pos.v][adj_pos.h])
              continue;

            discovered[adj_pos.v][adj_pos.h] = true;

            const auto& adj_state = hallway_[adj_pos.v][adj_pos.h];
            if (adj_state == State::Empty)
              continue;
            
            to_visit.push(adj_pos);
          }
        }

        max_size = max(max_size, size);
      }
    }
    */
  }

private:
  /// @param[in]      cv_pos   Currently visiting vertex position in `pos2_t`
  /// @param[in]      visited  Visited state
  /// @param[in, out] out_size Size of connected component measured by `DFS_Recur`
  void DFS_Recur(const pos2_t& cv_pos, vector<vector<bool>>& visited, size_t& out_size) const {

    visited[cv_pos.v][cv_pos.h] = true;

    (++out_size); // Increase size

    // find all cv_pos's adjacent!
    for (const auto& adj_pos: FindAdjacentPoses(cv_pos)) {
      if (visited[adj_pos.v][adj_pos.h]) // Already visited
        continue;
      if (state_[adj_pos.v][adj_pos.h] == State::Empty) // Not a garbage
        continue;

      DFS_Recur(adj_pos, visited, out_size); 
    }
  }

private:
  vector<vector<State>> state_; // state for pos2_t(v, h)
};

auto main() -> int
{
  {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
  }

  int N, M, K;
  cin >> N >> M >> K;

  const auto& v_size = M;   // [1, 100] vetical size of hallway
  const auto& h_size = N;   // [1, 100] horizontal size of hallway
  const auto& g_count = K;  // [1, v_size * h_size]

  HallWay hw(v_size, h_size, g_count); // Conduct remaining input in `Hallway`'s constructor

  const auto max_size = hw.CalConnectedComponentMaxSize();
  cout << max_size;

  return EXIT_SUCCESS;
}