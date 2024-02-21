// title: 백준 1753 최단 경로 G4
// date: 13:49 15:23 80
// 다익스트라의 priority queue 에 넣는건 gEdge가 아니다.
#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>

using namespace std;
class WGraph {
public: // Type Aliases
    using Pos_t = int;
    using Weight_t = int;
public: // Static Constants
    static constexpr Weight_t kInfiniteWeight = numeric_limits<Weight_t>::max();
    static constexpr Pos_t kInvalidPos = -1;
public: // Inner Struct for Priority Queue
    struct gEdge {
        Pos_t adj_pos = kInvalidPos;
        Weight_t weight = kInfiniteWeight;
    };
public:
    WGraph(int vertex_size, int edge_size) 
        : adj_lists_(vertex_size + 1, vector<gEdge>())
    {
        for (size_t e = 0; e < edge_size; ++e) {
            Pos_t s_pos, e_pos;  Weight_t w;
            cin >> s_pos >> e_pos >> w;
            adj_lists_[s_pos].push_back(gEdge{ e_pos, w });
        }

        #ifdef PS_DEBUG
        PrintAdjacentList();
        #endif //PS_DEBUG 
    }
    inline size_t size_v() const {
        return adj_lists_.size();
    }

public:

    // ** Get All shortest distance from start_vertex to all vertex using Dijkstra's Algorithm **
    void GetAllShortestDistanceFrom(Pos_t start_vertex, vector<Weight_t>& out_distance) {
        auto& shortest_distance_from_s = out_distance; // just renaming

        static auto gedge_weight_ascend_pred = [](const gEdge& l, const gEdge& r) { 
            if (l.weight != r.weight) return l.weight > r.weight;
            else return l.adj_pos > l.adj_pos;
        };
        priority_queue<gEdge, vector<gEdge>, decltype(gedge_weight_ascend_pred)> to_visit(gedge_weight_ascend_pred);

        shortest_distance_from_s[start_vertex] = 0;
        to_visit.push(gEdge{ start_vertex, 0 });

        while (!to_visit.empty()) {
            const auto [cv_pos, cv_w] = to_visit.top();
            to_visit.pop();

            if (shortest_distance_from_s[cv_pos] < cv_w)
                continue;

            for (const auto& adj_edge: adj_lists_[cv_pos]) {
                const auto& [adj_v, adj_w] = adj_edge;

                // [(start_vertex -> cv_pos) -adj_w-> adj_v]
                const auto& shortest_distance_from_s_new = cv_w + adj_w;

                // [start_vertex -> adj_v] direct shortest path exists?
                auto& shortest_distance_from_s_cache = shortest_distance_from_s[adj_v];

                if (shortest_distance_from_s_new >= shortest_distance_from_s_cache)
                    continue;
                
                shortest_distance_from_s_cache = shortest_distance_from_s_new; // Update cache
                to_visit.push(gEdge{adj_v, shortest_distance_from_s_cache});
            }
        }
    }

private:
    vector< vector<gEdge> > adj_lists_;


#ifdef PS_DEBUG
    void PrintAdjacentList() const {
        cout << "> Adjacent List: \n";
        for (size_t v = 1; v < size_v(); ++v) {
            cout << v << " | ";
            for (const auto& [adj_v, adj_w]: adj_lists_[v]) {
                cout << "(" << adj_v << ", " << adj_w << ") ";
            }
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

    int V, E;
    int K;
    cin >> V >> E;
    cin >> K;

    const auto& vertex_size = V; // [1, 20000]
    const auto& edge_size = E; // [1, 300000]
    const auto& start_vertex = K; // [1, V]

    WGraph graph(vertex_size, edge_size);
    vector<WGraph::Weight_t> distance(graph.size_v(), WGraph::kInfiniteWeight);
    // method's return value recorded in `distance` vector
    graph.GetAllShortestDistanceFrom(start_vertex, distance); 

    for (size_t v = 1; v < graph.size_v(); ++v) {
        if (distance[v] == WGraph::kInfiniteWeight)
            cout << "INF";
        else
            cout << distance[v];
        cout << '\n';
    }

    return 0;
}