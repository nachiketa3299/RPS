// title: ¾Ë°í½ºÆÌ SORTGAME Sorting Game Áß
// date: 13:48

#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <unordered_set>

using namespace std;

using Weight_t = int;
constexpr Weight_t kInfiniteWeight = numeric_limits<Weight_t>::max();
constexpr Weight_t kZeroWeight = 0;
constexpr int kPathFindError = -1;

using Pos_t = int;
constexpr Pos_t kInvalidPos = -1;

using Seq_t = std::vector<int>;

class SeqGraph {
public:
    SeqGraph(std::size_t seq_size)
        : seq_(seq_size)
        , sorted_seq_(seq_size)
        , seq_size_(seq_size)
    {
        static const auto input_lmbd = [](auto& e) { cin >> e; return e; };
        std::transform(seq_.begin(), seq_.end(), seq_.begin(), input_lmbd);
        // No redundant element exists
        std::iota(sorted_seq_.begin(), sorted_seq_.end(), 1);
        // No need to populate graph
    }
    inline std::size_t size() const {
        return sorted_seq_.size();
    }
    std::vector<Seq_t> MakeAdjacentSeqs(const Seq_t& seq) {
        std::vector<Seq_t> ret;
        for (std::size_t i = 0; i < seq_size_; ++i) {
            for (std::size_t j = i + 2; j < seq_size_; ++j) {
                auto seq_copy(seq);
                const auto& r_s = std::next(seq_copy.begin(), i);
                const auto& r_e = std::next(seq_copy.begin(), j);
                std::reverse(r_s, r_e);
                ret.push_back(seq_copy);
            }
        }
        return ret;
    }

    Weight_t BFS_ShortestPath() {
        std::queue<Seq_t> to_visit;
        std::map<Seq_t, Weight_t> distance;

        to_visit.push(seq_);
        distance[to_visit.front()] = kZeroWeight;

        while (!to_visit.empty()) {
            const auto cv_seq = to_visit.front();
            to_visit.pop();

            if (cv_seq == sorted_seq_)
                return distance[sorted_seq_];

            for (const auto& adj_seq: MakeAdjacentSeqs(cv_seq)) {
                if (!(distance.count(adj_seq) == 0)) // never visited
                    continue;

                distance[adj_seq] = distance[cv_seq] + 1;
                to_visit.push(adj_seq);
            }
        }
        return kInfiniteWeight;
    }

private:
    Seq_t seq_;
    Seq_t sorted_seq_;
    std::size_t seq_size_;
};

auto main() -> int
{
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr); cout.tie(nullptr);
    }

    int C; cin >> C;
    const auto& tc_count = C; // [1, 1'000]

    for (std::size_t t = 0; t < tc_count; ++t) {

        int N; cin >> N;
        const auto& seq_size = N; // [1, 8];

        SeqGraph s_graph(seq_size);

        const auto dist = s_graph.BFS_ShortestPath();
        switch(dist) {
            case kInfiniteWeight:
                cout << kPathFindError;
                break;
            default:
                cout << dist;
                break;
        }
        cout << '\n';
    }


    return 0;
}