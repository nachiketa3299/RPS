// * Title: 백준 24444 알고리즘 수업 - 너비 우선 탐색 1
// * Time: 12:29 13:11 (42)
// 다신 풀고싶지 않음

#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>

using namespace std;
class Graph {
public:
  using Pos_t = int;
  using Weight_t = int;
public:
  static constexpr Pos_t kInvalidPos = -1;
  static constexpr Weight_t kInfiniteWeight = numeric_limits<Weight_t>::max();
  static constexpr Weight_t kZeroPos = 0;
  static constexpr int kPathFindError = 0;
public:
  Graph(size_t vertex_size, size_t edge_size) 
    : adj_lists_(vertex_size + 1, vector<Pos_t>())
    , path_parents_(vertex_size + 1)
    , visit_order_(vertex_size + 1)
  {
    for (size_t e = 0; e < edge_size; ++e) {
      Pos_t u, v; cin >> u >> v;
      // u[1, v), v(u, N], u != v
      // no redundant (u, v) pair exists
      adj_lists_[u].push_back(v);
      adj_lists_[v].push_back(u);
    }
    for (auto& cadj_list: adj_lists_)
      sort(cadj_list.begin(), cadj_list.end(), less<Pos_t>());
  };
  inline size_t size_v() const {
    return adj_lists_.size();
  }
  void BFS_FindPathParents(const Pos_t& s_pos) {
    queue<Pos_t> to_visit;
    vector<bool> discovered(size_v(), false);
    fill(visit_order_.begin(), visit_order_.end(), 0);
    to_visit.push(s_pos);
    discovered[to_visit.front()] = true;
    auto order = 0;

    while (!to_visit.empty()) {
      const auto cv_pos = to_visit.front();
      visit_order_[cv_pos] = (++order);

      to_visit.pop();

      for (const auto& adj_pos: adj_lists_[cv_pos]) {
        if (discovered[adj_pos])
          continue;
        discovered[adj_pos] = true;
        to_visit.push(adj_pos);
      }

    } // End of BFS
    // End of function
  }
private:
  vector<vector<Pos_t>> adj_lists_;
  vector<Pos_t> path_parents_;
public:
  vector<int> visit_order_;
};

auto main() -> int
{
  {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
  }

  int N, M, R;
  cin >> N >> M >> R;
  const auto& vertex_size = N; // [5, 100'000]
  const auto& edge_size = M; // [1, 200'000]
  const auto& s_pos = R; // [1, vertex_size]
  Graph graph(vertex_size, edge_size);
  graph.BFS_FindPathParents(s_pos);

  for (size_t v = 1; v < graph.size_v(); ++v) {
    cout << graph.visit_order_[v] << '\n';
  }


  return EXIT_SUCCESS;
}