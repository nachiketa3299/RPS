// title: 백준 1504 특정한 최단 경로 G4
// date: 13:22 14:34 72

#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <limits>

using namespace std;
constexpr int kNoPathError = -1;

class Graph {
public:
    using Weight_t = int;
    using Pos_t = int;
    static constexpr Weight_t kInifiniteWeight = numeric_limits<Weight_t>::max();
    static constexpr Weight_t kZeroWeight = 0;
    using g_pair = pair<Weight_t, Pos_t>;
    using PQ_GP_ASC = priority_queue< g_pair, vector<g_pair>, greater<g_pair> >;

public:
    Graph(size_t vertex_size, size_t edge_size) 
        : adj_lists_(vertex_size + 1)
    {
        for (size_t e = 0; e < edge_size; ++e) {
            int a, b, c; 
            cin >> a >> b >> c; // a <-c-> b
            adj_lists_[a].push_back(make_pair(c, b));
            adj_lists_[b].push_back(make_pair(c, a));
        }

        #ifdef PS_DEBUG
        PrintAdjacentLists();
        #endif //PS_DEBUG 
    }
    inline size_t size_v() const {
        return adj_lists_.size();
    }

    Weight_t Dijkstra(Pos_t s_pos, Pos_t e_pos) {
        vector<Weight_t> out_distance(size_v() + 1, kInifiniteWeight);

        PQ_GP_ASC to_visit;

        out_distance[s_pos] = kZeroWeight;
        to_visit.push(make_pair(kZeroWeight, s_pos));

        while (!to_visit.empty()) {
            const auto [cv_w, cv_pos] = to_visit.top();
            to_visit.pop();

            if (cv_w > out_distance[cv_pos])
                continue;

            for (const auto& [adj_w, adj_pos]: adj_lists_[cv_pos]) {

                auto& dist_cache = out_distance[adj_pos];
                const auto& dist_new = cv_w + adj_w;

                if (!(dist_new < dist_cache))
                    continue;

                dist_cache = dist_new;
                to_visit.push(make_pair(dist_new, adj_pos));
            }
        }

        const auto& dist = out_distance[e_pos];
        return dist;
    }

#ifdef PS_DEBUG
    void PrintAdjacentLists() const {
        cout << "> Adjacent List: \n";
        for (size_t v = 1; v < size_v(); ++v) {
            cout << v << " | ";
            for (const auto& [adj_w, adj_p]: adj_lists_[v]) {
                cout << "(" << adj_w << ", " << adj_p << ") ";
            }
            cout << '\n';
        }
        cout << '\n';
    }
#endif //PS_DEBUG 

private:
    vector< vector<g_pair> > adj_lists_;
};

#ifdef PS_DEBUG
void PrintWeights(const vector<Graph::Weight_t>& weights) {
    cout << "> Weights: ";
    for (size_t v = 1; v < weights.size(); ++v) {
        const auto& cw = weights[v];

        if (cw == Graph::kInifiniteWeight)
            cout << "INF";
        else
            cout << cw;
        cout << " ";
    }
    cout << '\n';
}
#endif //PS_DEBUG 

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int N, E;
    cin >> N >> E;
    const int& vertex_size = N; // [2, 800]
    const int& edge_size = E; // [0, 200'000]

    Graph graph(vertex_size, edge_size);

    int v1, v2;
    cin >> v1 >> v2;

    Graph::Pos_t S1 = 1;
    Graph::Pos_t EN = N;

    vector<Graph::Weight_t> ds_S1_to_v1(vertex_size + 1, Graph::kInifiniteWeight);
    vector<Graph::Weight_t> ds_v1_to_v2(vertex_size + 1, Graph::kInifiniteWeight);
    vector<Graph::Weight_t> ds_v2_to_EN(vertex_size + 1, Graph::kInifiniteWeight);

    static const auto is_all_valid = [](Graph::Weight_t a, Graph::Weight_t b, Graph::Weight_t c) { 
        return !(a == Graph::kInifiniteWeight || b == Graph::kInifiniteWeight || c == Graph::kInifiniteWeight);
    };

    const auto S1_v1 = graph.Dijkstra(S1, v1);
    const auto v1_v2 = graph.Dijkstra(v1, v2);
    const auto v2_EN = graph.Dijkstra(v2, EN);

    bool dist_v1_v2_valid = is_all_valid(S1_v1, v1_v2, v2_EN);
    const auto dist_v1_v2 = S1_v1 + v1_v2 + v2_EN;

    const auto S1_v2 = graph.Dijkstra(S1, v2);
    const auto v2_v1 = graph.Dijkstra(v2, v1);
    const auto v1_EN = graph.Dijkstra(v1, EN);

    bool dist_v2_v1_valid = is_all_valid(S1_v2, v2_v1, v1_EN);
    const auto dist_v2_v1 = S1_v2 + v2_v1 + v1_EN;

    if (dist_v1_v2_valid && dist_v2_v1_valid) {
        cout << min(dist_v1_v2, dist_v2_v1);
    }
    else if (!dist_v1_v2_valid && dist_v2_v1_valid) {
        cout << dist_v2_v1;
    }
    else if (dist_v1_v2_valid && !dist_v2_v1_valid) {
        cout << dist_v1_v2;
    }
    else /* (!dist_v1_v2_valid && !dist_v2_v1_valid) */ {
        cout << kNoPathError;
    }


    return 0;
}