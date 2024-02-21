// * Title: 백준 1987 알파벳 G4
// * Time: 12:18 13:28
// Failed : DFS Application 에 대한 고찰이 필요함

#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <utility>
#include <limits>
#include <deque>
#include <set>

using namespace std;

struct pos2_t {
  using pos_t = int;
  static constexpr pos_t kInvalidPos = -1;  
  inline static vector<pos2_t> GetOffsets() {
    return { {-1, 0}, {+1, 0}, {0, +1}, {0, -1} };
  }
  inline bool is_in_v_bound(pos_t min_bound, pos_t max_bound) const {
    return min_bound <= v && v < max_bound;
  }
  inline bool is_in_h_bound(pos_t min_bound, pos_t max_bound) const {
    return min_bound <= h && h < max_bound;
  }
  pos2_t operator+(const pos2_t& other) const {
    return { v + other.v,  h + other.h };
  }

  pos_t v { kInvalidPos };
  pos_t h { kInvalidPos };
};

class BGraph {
public:
  using pos_t = pos2_t::pos_t;
  using alphabet_t = char;
  using weight_t = int;
  static constexpr weight_t kInfiniteWeight = numeric_limits<weight_t>::max();
  static constexpr weight_t kZeroWeight = 0;
  using s_pair = pair<string, pos2_t>;

public:
  BGraph(size_t v_size, size_t h_size) 
    : board_(v_size, vector<alphabet_t>(h_size))
  {
    for (auto v = 0; v < size_v(); ++v)
      for (auto h = 0; h < size_h(); ++h)
        cin >> board_[v][h];
  };
  inline size_t size_v() const {
    return board_.size();
  }
  inline size_t size_h() const {
    return board_.front().size();
  }

  vector<s_pair> FindAdjacentPair(const s_pair& cv_pair) const {
    const auto& [cv_s_path, cv_pos] = cv_pair;
    vector<s_pair> ret;
    for (const auto& offset: pos2_t::GetOffsets()) {
      const auto c_pos = offset + cv_pos;
      if (!(c_pos.is_in_v_bound(0, size_v())))
        continue;
      if (!(c_pos.is_in_h_bound(0, size_h())))
        continue;
      const auto& c_char = board_[c_pos.v][c_pos.h];
      if (!(cv_s_path.find(c_char) == string::npos))
        continue;
      ret.push_back({ string{ cv_s_path + c_char }, c_pos });
    }
    return ret;
  }

  map<string, weight_t> BFS_ShortestPath(const pos2_t& s_pos) {
    queue<s_pair> to_visit;
    to_visit.push({ string{ board_[s_pos.v][s_pos.h] }, s_pos });
    const auto& [init_s_path, init_pos] = to_visit.front();

    map<string, weight_t> distances;
    distances[init_s_path] = 1;

    while (!to_visit.empty()) {
      const auto cv_pair = to_visit.front();
      const auto& [cv_s_path, cv_pos] = cv_pair;
      to_visit.pop();

      for (const auto& adj_pair: FindAdjacentPair(cv_pair)) {
        const auto& [adj_s_path, adj_pos] = adj_pair;

        if (!(distances.count(adj_s_path) == 0))
          continue;

        distances[adj_s_path] = distances[cv_s_path] + 1;
        to_visit.push({ adj_s_path, adj_pos });
      }
    }

    return distances;
  }

  set<string> DFS_Path(const pos2_t& s_pos) {
    static set<string> discovered;
    return DFS_Recur({string {board_[s_pos.v][s_pos.h]}, s_pos}, discovered);
  }

  set<string> DFS_Recur(const s_pair& cv_pair, set<string>& discovered) {
    const auto& [cv_s_path, cv_pos] = cv_pair;
    discovered.insert(cv_s_path);

    for (const auto& adj_pair: FindAdjacentPair(cv_pair)) {
      const auto& [adj_s_path, adj_pos] = adj_pair;
      if (!(discovered.find(adj_s_path) == discovered.end()))
        continue;
      DFS_Recur(adj_pair, discovered);
    }
    return discovered;
  }

private:
  vector<vector<alphabet_t>> board_;
};

auto main() -> int
{
  {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
  }

  int R, C;
  cin >> R >> C;
  const auto& b_v_size = R;
  const auto& b_h_size = C;
  BGraph bg(b_v_size, b_h_size);
  const auto dist_map  = bg.DFS_Path({0, 0});

  const auto max_s_path = *max_element(dist_map.cbegin(), dist_map.cend(), 
    [](const auto& l, const auto& r) {
      return l.size() < r.size();
    }
  );

  cout << max_s_path.size();

  return EXIT_SUCCESS;
}