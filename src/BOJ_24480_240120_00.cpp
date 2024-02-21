// * Title: 백준 24480 알고리즘 수업 - 깊이 우선 탐색 2 S2
// * Time: 21:21 22:21


#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

vector<int> DFS(int cv_pos, const vector<vector<int>>& adj_lists) {
  static auto cv_order = 0;

  static vector<bool> visited(adj_lists.size(), false);
  static vector<int> visit_order(adj_lists.size(), 0);

  visited[cv_pos] = true;
  visit_order[cv_pos] = (++cv_order);
  
  for (const auto& adj_pos: adj_lists[cv_pos]) {
    if (visited[adj_pos])
      continue;
    DFS(adj_pos, adj_lists);
  }
  return visit_order;
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
  const auto& start_vertex = R; // [1, vertex_size]

  vector<vector<int>> adj_lists(vertex_size + 1);
  for (auto e = 0; e < edge_size; ++e) {
    int u, v;
    cin >> u >> v;
    adj_lists[u].push_back(v);
    adj_lists[v].push_back(u);
  }
  for (auto& list: adj_lists)
    sort(list.begin(), list.end(), greater<int>());

  #ifdef PS_DEBUG
  cout << "> ADJ List:\n";
  for (auto v = 1; v <= vertex_size; ++v) {
    cout << v << " | ";
    for (const auto& adj_v: adj_lists[v])
      cout << adj_v << " ";
    cout << '\n';
  }
  cout << "\n";
  #endif //PS_DEBUG 

  const auto visit_order = DFS(start_vertex, adj_lists);

  for (auto v = 1; v <= vertex_size; ++v)
    cout << visit_order[v] << '\n';

  return EXIT_SUCCESS;
}