// title: 백준 10282 해킹 G4
// date: 15:44 16:46 62
// 다익스트라 한번 정리해야 할 것 같음
#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <limits>

using namespace std;

using Pos_t = int;
using Weight_t = int;

constexpr Weight_t kInfiniteWeight = numeric_limits<Weight_t>::max();
constexpr Weight_t kZeroWeight = 0;
constexpr Weight_t kMinWeight = -1;


class WGraph {
    using s_pair = pair<Weight_t, Pos_t>;
public:
    WGraph(int vertex_size)
        : adj_lists_(vertex_size + 1)
        , s_distance_from_s_(vertex_size + 1, kInfiniteWeight)
    {}
    inline size_t size_v() const {
        return adj_lists_.size();
    }
    void AddEdge(Pos_t s_pos, Pos_t e_pos, Weight_t weight) {
        adj_lists_[s_pos].push_back(make_pair(weight, e_pos));
    }

public:
    void UpdateAllShortestDistanceFrom(int start_vertex) {

        priority_queue<s_pair, vector<s_pair>, greater<s_pair>> to_visit; 

        // Initialzie Dijkstra Condition
        to_visit.push(make_pair(kZeroWeight, start_vertex));
        s_distance_from_s_[start_vertex] = kZeroWeight;

        // Process Dijkstra
        while (!to_visit.empty()) {
            const auto [cv_w, cv_p] = to_visit.top();
            to_visit.pop();


            if (!(cv_w <= s_distance_from_s_[cv_p])) // warning
                continue;


            for (const auto& [adj_w, adj_p]: adj_lists_[cv_p]) {
                const auto distance_new = cv_w + adj_w;
                auto& distance_cache = s_distance_from_s_[adj_p];

                if (distance_new >= distance_cache)
                    continue;
                
                distance_cache = distance_new;
                to_visit.push(make_pair(distance_new, adj_p));

            }
        }

        for (const auto& c_dist: s_distance_from_s_) {
            if (c_dist == kInfiniteWeight)
                 continue;
            max_distance = max(max_distance, c_dist);
            connected_component_size++;
        }

    }

private:
    vector< vector<s_pair> > adj_lists_;
    vector<Weight_t> s_distance_from_s_;
public:
    size_t connected_component_size = 0;
    Weight_t max_distance = kMinWeight;

#ifdef PS_DEBUG
public:
    void PrintAdjacentList() const {
        cout << "> Adjacent List:\n";
        for (size_t v = 1; v < size_v(); ++v) {
            cout << v << " | ";
            for (const auto& [adj_w, adj_v]: adj_lists_[v])
                cout << "(" << adj_v << ", " << adj_w << ") ";
            cout << '\n';
        }
        cout << '\n';
    }
#endif //PS_DEBUG 
};

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int TC_count; cin >> TC_count; // [1, 100] natural number

    for (size_t tc = 0; tc < TC_count; ++tc) { // PER TESTCASE

    int n, d, c;
    cin >> n >> d >> c;

    const auto& vertex_size = n; // [1, 10'000]
    const auto& edge_size = d; // [1, 100'000]
    const auto& start_vertex = c; // [1, vertex_size]

    WGraph graph(vertex_size);

    // Add Edges to graph
    for (size_t e = 0; e < edge_size; ++e) {
        int a, b, s;
        cin >> a >> b >> s;
        const auto& e_e_pos = a; // [1, n], != e_e_pos
        const auto& e_s_pos = b; // [1, n], != e_s_pos
        const auto& e_weight = s; // [0, 1'000]
        // no redundant (e_s_pos, e_e_pos) pair exists per testcase

        graph.AddEdge(e_s_pos, e_e_pos, e_weight);

    }

    #ifdef PS_DEBUG
    graph.PrintAdjacentList();
    #endif //PS_DEBUG 

    graph.UpdateAllShortestDistanceFrom(start_vertex);
    cout << graph.connected_component_size << " ";
    cout << graph.max_distance << '\n';

    } // PER TESTCASE

    return 0;
}