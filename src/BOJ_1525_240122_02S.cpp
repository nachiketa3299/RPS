// * Title: 백준 1525 퍼즐
// * Time: 11:22 12:12 (50)
// 쉬운 문제잖아...? map 의 사용.

#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>
#include <queue>
#include <map>
#include <utility>

#define SIZE_V 3
#define SIZE_H 3

using namespace std;

struct pos2_t {
  using pos_t = int;
  static constexpr pos_t kInvalidPos = -1;
  static vector<pos2_t> GetOffsets() {
    return { {-1, 0}, {+1, 0}, {0, -1}, {0, +1} };
  }
  pos2_t operator+(const pos2_t& other) const {
    return {v + other.v, h + other.h };
  }
  inline bool is_in_v_bound(size_t min_bound, size_t max_bound) const {
    return min_bound <= v && v < max_bound;
  }
  inline bool is_in_h_bound(size_t min_bound, size_t max_bound) const {
    return min_bound <= h && h < max_bound;
  }

  pos_t v = kInvalidPos;
  pos_t h = kInvalidPos;
};

class BGraph {
public:
  using pos_t = pos2_t::pos_t;
  using weight_t = int;
  static constexpr weight_t kInfiniteWeight = numeric_limits<weight_t>::max();
  static constexpr weight_t kZeroWeight = 0;
  static constexpr int kPathFindError = -1;
  // (Board state as str, Cv position) 
  using s_pair = pair<string, pos2_t>;

public:
  BGraph() 
    : init_b_str_("")
  {
    // Input board as string
    for (auto v = 0; v < size_v(); ++v) {
      for (auto h = 0; h < size_h(); ++h) {
        char c; cin >> c;
        init_b_str_ += c;

        // Save search start position
        if (c == '0')
          s_pos_ = { v, h };
      }
    }
  };

public:
  static char& get_at(string& str, const pos2_t& pos) {
    return str[SIZE_V * pos.v + pos.h];
  }
  vector<pos2_t> FindAdjacentPoses(const pos2_t& cv_pos) {
    vector<pos2_t> ret;
    for (const auto& offset: pos2_t::GetOffsets()) {
      const auto c_pos = cv_pos + offset;
      if (!(c_pos.is_in_v_bound(0, size_v())))
        continue;
      if (!(c_pos.is_in_h_bound(0, size_h())))
        continue;
      ret.push_back(c_pos);
    }
    return ret;
  }

  vector<s_pair> FindAdjacentPairs(const s_pair& cv_pair) {
    const auto& [cv_b_state, cv_pos] = cv_pair;
    vector<s_pair> ret;
    for (const auto& adj_pos: FindAdjacentPoses(cv_pos)) {
      auto adj_b_state(cv_b_state);
      swap(get_at(adj_b_state, cv_pos), get_at(adj_b_state, adj_pos));
      ret.push_back({adj_b_state, adj_pos});
    }
    return ret;
  }
  weight_t BFS_ShortestPath() {
    const string kPathTarget("123456780");
    queue<s_pair> to_visit;
    map<string, weight_t> distances; 

    to_visit.push({init_b_str_, s_pos_});
    distances[init_b_str_] = kZeroWeight;

    while (!to_visit.empty()) {
      const auto cv_pair = to_visit.front();
      const auto& [cv_b_state, cv_pos] = cv_pair;

      if (cv_b_state == kPathTarget)
        return distances[cv_b_state];

      to_visit.pop();

      // cv_pair : 123 405 789 -> ("123405789", (1, 1))
      // adj_pair: 
      //           123 045 789 -> ("123045789", (1, 0))
      //           123 450 789 -> ("123450789", (1, 2))
      //           103 425 789 -> ("103425789", (0, 1))
      //           123 485 709 -> ("123485709", (2, 1))

      for (const auto& adj_pair: FindAdjacentPairs(cv_pair)) {
        const auto& [adj_b_state, adj_pos] = adj_pair;

        if (!(distances.count(adj_b_state) == 0))
          continue;
        
        distances[adj_b_state] = distances[cv_b_state] + 1;
        to_visit.push(adj_pair);
      }
    }

    return kInfiniteWeight;
  };

public:
  inline static size_t size_v() {
    return SIZE_V;
  }
  inline static size_t size_h() {
    return SIZE_H;
  }

private:
  string init_b_str_;
  pos2_t s_pos_;
};

auto main() -> int
{
  {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
  }

  BGraph bg;
  const auto dist = bg.BFS_ShortestPath();
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