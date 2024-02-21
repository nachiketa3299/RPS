// title:  백준 1753 최단 경로 G4
// date: 1:16 2:17 F 
// 우선순위 큐 오름차순 & 내림차순? 
#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
using Pos_t = size_t;
using Weight_t = int;

struct Edge {
    static constexpr Weight_t kInvalidWeight = numeric_limits<Weight_t>::max();
    static constexpr Pos_t kInvalidPos = -1;
    Pos_t s_pos = kInvalidPos;
    Pos_t e_pos = kInvalidPos;
    Weight_t weight = kInvalidWeight;
};
istream& operator>>(istream& is, Edge& edge) {
    is >>  edge.s_pos >> edge.e_pos >> edge.weight;
    return is;
}

class WGraph {
    struct gEdge {
        Pos_t adj_p = Edge::kInvalidPos;
        Weight_t weight = Edge::kInvalidWeight;
        bool operator>(const gEdge& right) const {
            return weight > right.weight;
        }
    };
public:
    WGraph(int vertex_size, int edge_size) 
        : adj_lists_(vertex_size + 1, vector<gEdge>())
    {
        for (size_t e = 0; e < edge_size; ++e) {
            Edge edge; cin >> edge;
            adj_lists_[edge.s_pos].push_back(gEdge{edge.e_pos, edge.weight});
        }

        #ifdef PS_DEBUG
        PrintAdjacentList();
        #endif //PS_DEBUG 
    }
    inline size_t size_v() const {
        return adj_lists_.size();
    }
    void GetAllShortestDistanceFrom(Pos_t s_pos, vector<Weight_t>& out_distance) const {
        priority_queue<gEdge, vector<gEdge>, greater<gEdge>> to_visit;

        to_visit.push(gEdge{s_pos, Edge::kInvalidWeight});
        out_distance[s_pos] = 0;

        while (!to_visit.empty()) {
            const auto [cv_p, _cv_w] = to_visit.top();
            to_visit.pop();
            for (const auto& [adj_p, adj_w]: adj_lists_[cv_p]) {

                auto& adj_p_distance_from_s_cache = out_distance[adj_p];
                const auto& adj_p_distance_from_s = out_distance[cv_p] + adj_w;

                if (adj_p_distance_from_s_cache <= adj_p_distance_from_s)
                    continue;
                
                // Update shortest distance
                adj_p_distance_from_s_cache = adj_p_distance_from_s;
                to_visit.push(gEdge{adj_p, adj_w});
            }
        }
    };

private:
    vector< vector<gEdge> > adj_lists_;
    
#ifdef PS_DEBUG
public:
    void PrintAdjacentList() const {
        cout << "> Adj List:\n";
        for (size_t v = 1; v < size_v(); ++v) {
            cout << v << " | ";
            for (auto& [e, w]: adj_lists_[v]) {
                cout << "(" << e << ", " << w << ") ";
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

    int V, E, K;
    cin >> V >> E;
    cin >> K;
    const auto& vertex_size = V; // [1, 2e4]
    const auto& edge_size = E; // [1, 3e5]
    const auto& start_vertex = K; // [1, vertex_size]

    WGraph graph(vertex_size, edge_size);
    vector<Weight_t> distance(vertex_size + 1, Edge::kInvalidWeight);
    graph.GetAllShortestDistanceFrom(start_vertex, distance);
    for (size_t v = 1; v <= vertex_size; ++v) {
        const auto& cdist = distance[v];
        if (cdist == Edge::kInvalidWeight)
            cout << "INF";
        else
            cout << cdist;
        cout << '\n';
    }

    return 0;
}