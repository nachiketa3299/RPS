// * Title: 백준 1525 퍼즐 G2
// * Time: 100
// Failed: 메모리 초과! 왜지??????? Map인게 문제인가?

#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <limits>
#include <map>

using namespace std;
struct Pos2_t {
  using Pos_t = int;
  static constexpr Pos_t kInvalidPos = -1;
  Pos_t v = kInvalidPos;
  Pos_t h = kInvalidPos;
  inline bool is_in_v_bound(size_t min_bound, size_t max_bound) const {
    return min_bound <= v && v < max_bound;
  }
  inline bool is_in_h_bound(size_t min_bound, size_t max_bound) const {
    return min_bound <= h && h < max_bound;
  }
  static vector<Pos2_t> GetOffsets() {
    return { { -1, 0 }, { +1, 0 },{ 0, -1 },{ 0, +1 }, };
  }
  Pos2_t operator+(const Pos2_t& other) const {
    return { v + other.v, h + other.h };
  }
  bool operator==(const Pos2_t& other) const {
    return v == other.v && h == other.h;
  }
};

class BGraph {
public:
  using Pos_t = Pos2_t::Pos_t;
  using Weight_t = int;
  static constexpr Weight_t kInfiniteWeight = numeric_limits<Weight_t>::max();
  static constexpr Weight_t kZeroWeight = 0;
  static constexpr int  kPathFindError = -1;
public:
  BGraph(size_t v_size, size_t h_size)
  : board_(v_size, vector<int>(h_size))
  , e_pos_({(int)(v_size - 1), (int)(h_size - 1)})
  { 
    for (auto v = 0; v < v_size; ++v) {
      for (auto h = 0; h < h_size; ++h) {
        char c; cin >> c;
        board_str_ += c;
        board_[v][h] = (int)(c - '0');
        if (c == '0') 
          s_pos_ = { v, h };
      }
    }
  }
  Weight_t BFS_ShortestPath() const {
    using g_pair = pair<Pos2_t, string>;

    queue<g_pair> to_visit;
    map<string, vector<vector<bool>>> discovered;
    map<string, vector<vector<Weight_t>>> distances;

    const auto init_b_str = board_str_;
    to_visit.push({s_pos_, init_b_str});
    discovered[init_b_str] = vector<vector<bool>>(size_v(), vector<bool>(size_h(), false));
    discovered[init_b_str][s_pos_.v][s_pos_.h] = true;
    distances[init_b_str] = vector<vector<Weight_t>>(size_v(), vector<Weight_t>(size_h(), kInfiniteWeight));
    
    distances[init_b_str][s_pos_.v][s_pos_.h] = kZeroWeight;
    const string target_b_str = "123456780";

    while(!to_visit.empty()) {
      const auto [cv_pos, cv_b_str] = to_visit.front();

      if (cv_b_str == target_b_str)
        return distances[cv_b_str][cv_pos.v][cv_pos.h];

      to_visit.pop();

      for (const auto& adj_pos: FindAdjacentPoses(cv_pos)) {
        auto adj_b_str(cv_b_str);
        swap(GetPosAt(*this, adj_b_str, cv_pos), GetPosAt(*this, adj_b_str, adj_pos));
        if (discovered.count(adj_b_str) == 0) {
          // This adjcent state was never been discovered
          discovered[adj_b_str] = vector<vector<bool>>(size_v(), vector<bool>(size_h(), false));
          distances[adj_b_str] = vector<vector<Weight_t>>(size_v(), vector<Weight_t>(size_h(), kInfiniteWeight));

          discovered[adj_b_str][adj_pos.v][adj_pos.h] = true;
          distances[adj_b_str][adj_pos.v][adj_pos.h] = distances[cv_b_str][cv_pos.v][cv_pos.h] + 1;
          to_visit.push({adj_pos, adj_b_str});
        }
        else {
          // This adjacent state was discovered before
          if (discovered[adj_b_str][adj_pos.v][adj_pos.h])
            continue;
          discovered[adj_b_str][adj_pos.v][adj_pos.h] = true;
          distances[adj_b_str][adj_pos.v][adj_pos.h] = distances[cv_b_str][cv_pos.v][cv_pos.h] + 1;
          to_visit.push({adj_pos, adj_b_str});
        }
      }
    }
    return kInfiniteWeight;
  }
  inline size_t size_v() const {
    return board_.size();
  }
  inline size_t size_h() const {
    return board_.front().size();
  }
  vector<Pos2_t> FindAdjacentPoses(const Pos2_t& cv_pos) const {
    vector<Pos2_t> ret;
    for (const auto& offset: Pos2_t::GetOffsets()) {
      const auto& c_pos = cv_pos + offset;
      if (!c_pos.is_in_v_bound(0, size_v()))
        continue;
      if (!c_pos.is_in_h_bound(0, size_h()))
        continue;
      ret.push_back(c_pos);
    }
    return ret;
  }
  inline static string MakeBoardString(const vector<vector<int>>& board) {
    string ret;
    for (auto v = 0; v < board.size(); ++v)
      for (auto h = 0; h < board[v].size(); ++h)
        ret += (char)(board[v][h] + '0');
    return ret;
  }
  inline static vector<vector<int>> MakeBoard(const string& b_str, size_t v_size, size_t h_size) {
    vector<vector<int>> ret(v_size, vector<int>(h_size));
    for (auto v = 0; v < v_size; ++v) {
      for (auto h = 0; h < h_size; ++h) {
        ret[v][h] = b_str[v_size * v + h] - '0';
      }
    }
    return ret;
  }
  static char& GetPosAt(const BGraph& g, string& b_str, const Pos2_t& pos) {
    return b_str[g.size_v() * pos.v + pos.h];
  }

private:
  vector<vector<int>> board_;
  string board_str_;
  Pos2_t s_pos_;
  Pos2_t e_pos_;
};

auto main() -> int
{
  {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
  }

  constexpr int board_v_size = 3;
  constexpr int board_h_size = 3;
  BGraph b(board_v_size, board_h_size);

  const auto dist = b.BFS_ShortestPath();
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