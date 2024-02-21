// * Title: ¾Ë°í½ºÆÌ 
// * Time: 

#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <map>

using namespace std;

class SeqGraph {
public: // Types
  using Seq_e_t = int;
  using Seq_t = vector<Seq_e_t>;
  using Weight_t = int;

public: // Constants
  static constexpr Weight_t kInifiniteWeight = numeric_limits<Weight_t>::max();
  static constexpr Weight_t kZeroWeight = 0;
  static constexpr Weight_t kPathFindError = -1;

public:
  SeqGraph(const Seq_t& seq) 
    : seq_(seq)
  { };
public:
  size_t size() const {
    return seq_.size();
  }

public:
  vector<Seq_t> FindAdjacentPoses(const Seq_t& seq) const {
    vector<Seq_t> ret;
    for (size_t i = 0; i < size(); ++i) {
      for (size_t j = i + 2; j <= size(); ++j) {
        auto seq_copy(seq);
        const auto rs = next(begin(seq_copy), i);
        const auto re = next(begin(seq_copy), j);
        reverse(rs, re);
        ret.push_back(seq_copy);
      }
    }
    return ret;
  }

public:
  Weight_t BFS_ShortestPath(const Seq_t& target_seq) {
    queue<Seq_t> to_visit;
    map<Seq_t, size_t> distance; // O(log {seq.size()})

    to_visit.push(seq_);
    distance[to_visit.front()] = kZeroWeight;

    while (!to_visit.empty()) {
      // > BFS Visiting
      const auto cv_seq = to_visit.front();
      to_visit.pop();
      
      if (cv_seq == target_seq)
        return distance[cv_seq];

      for (const auto& adj_seq: FindAdjacentPoses(cv_seq)) {
        // > BFS Discovering
        if (!(distance.count(adj_seq) == 0)) // Already Visited?
          continue;
        distance[adj_seq] = distance[cv_seq] + 1;
        to_visit.push(adj_seq);
      }
    }
    return kInifiniteWeight;
  }
  
private:
  Seq_t seq_;
};

auto main() -> int
{
  using namespace std;
  {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
  }

  size_t TC_count; cin >> TC_count;
  for (size_t tc = 0; tc < TC_count; ++tc) {
    int N; cin >> N;
    const auto& seq_size = N;
    static const auto input_seq = [](auto& e) { cin >> e; return e; };

    SeqGraph::Seq_t init_seq(N);
    transform(init_seq.begin(), init_seq.end(), init_seq.begin(), input_seq);

    auto sorted_seq(init_seq);
    sort(sorted_seq.begin(), sorted_seq.end(), less<SeqGraph::Seq_e_t>());

    SeqGraph s_graph(init_seq);
    const auto distance = s_graph.BFS_ShortestPath(sorted_seq);

    switch (distance) {
      case SeqGraph::kInifiniteWeight:
        cout << SeqGraph::kPathFindError;
        break;
      default:
        cout << distance;
        break;
    }
    cout << '\n';
  } // TC_loop ends

  return EXIT_SUCCESS;
}