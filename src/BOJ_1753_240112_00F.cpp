// title: 백준 1753 최단 경로 G4
// date: 15:34 16:42
#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>

using namespace std;

// start != end
struct WeightedEdge {
    int start = 0;
    int end = 0;
    int weight = 0; // [1, 10] natrual number
    friend istream& operator>>(istream& is, WeightedEdge& ref) {
        is >> ref.start >> ref.end >> ref.weight;
        return is;
    }
};

class DiGraph {
public:
    constexpr static int kPathFindError = -1;
private:
    constexpr static int kInfDistance = numeric_limits<int>::max();
    struct AdjWEdge {
        AdjWEdge() = default;
        AdjWEdge(const int& iadj_vertex, const int& iadj_weight)
            : adj_vertex(iadj_vertex)
            , adj_weight(iadj_weight)
        {}
        int adj_vertex = 0;
        int adj_weight = 0;
        #ifdef PS_DEBUG
        friend ostream& operator<<(ostream& os, const AdjWEdge& ref) {
            os << ref.adj_vertex << '(' << ref.adj_weight << ')';
            return os;
        }
        #endif //PS_DEBUG 
    };
public:
    DiGraph(const size_t& v_count, const vector<WeightedEdge> w_edges, const size_t& ibfs_start_v)
        : adj_lists_(v_count + 1)
        , min_dist_from_bfs_start_v_(v_count + 1, kInfDistance)
        , bfs_start_v(ibfs_start_v)
    {
        // Self distance is 0
        min_dist_from_bfs_start_v_[bfs_start_v] = 0;

        for (const auto& [v_s, v_e, w]: w_edges) {
            adj_lists_[v_s].push_back(AdjWEdge(v_e, w));
            // Update direct adjacent distance 
            if (v_s == bfs_start_v) 
                min_dist_from_bfs_start_v_[v_e] = w;
        }
    }
    inline size_t size_v() const {
        return adj_lists_.size();
    }
    int GetMinDistance(const size_t& v_end) const {
        if (bfs_start_v == v_end)
            return min_dist_from_bfs_start_v_[v_end];

        vector<bool> visited(size_v(), false);
        queue<size_t> to_visit;

        to_visit.push(bfs_start_v);
        visited[to_visit.front()] = true;

        while (!to_visit.empty()) {
            const auto cvisit_v = to_visit.front(); 
            to_visit.pop();

            for (const auto& [adj_v, adj_w]: adj_lists_[cvisit_v]) {
                if (visited[adj_v])
                    continue;

                min_dist_from_bfs_start_v_[adj_v] = min(min_dist_from_bfs_start_v_[adj_v], min_dist_from_bfs_start_v_[cvisit_v] + adj_w);

                visited[adj_v] = true;
                to_visit.push(adj_v);

                if (adj_v == v_end)
                    return min_dist_from_bfs_start_v_[v_end];
            }
        }
        return kPathFindError;
    }

#ifdef PS_DEBUG
public:
    void Print() const {
        for (size_t v = 1; v < size_v(); ++v) {
            cout << v << " | ";
            for (const auto& adj_wedge: adj_lists_[v]) {
                cout << adj_wedge << " ";
            }
            cout << '\n';
        }
    }
#endif //PS_DEBUG 
private:
    vector< vector<AdjWEdge> > adj_lists_;
    mutable vector<int> min_dist_from_bfs_start_v_;
public:
    const size_t bfs_start_v;
};

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }
    /* === INPUT === */
    // Warning: directed graph
    int V, E, K;
    cin >> V >> E;
    cin >> K;

    /* vertices are indexed { 1, 2, ... v_count } */
    const auto& v_count      = V; // [1, 2e4]
    const auto& e_count      = E; // [1, 3e5]
    const auto& start_vertex = K; // [1, V]

    vector<WeightedEdge> w_edges(e_count);
    for (auto& w_edge: w_edges) 
        cin >> w_edge;

    DiGraph graph(v_count, w_edges, start_vertex);

    for (size_t end_vertex = 1; end_vertex <= v_count; ++end_vertex) {
        const auto& path_find_result = graph.GetMinDistance(end_vertex);
        switch  (path_find_result) {
            case DiGraph::kPathFindError:
                cout << "INF";
                break;
            default:
                cout << path_find_result;
                break;
        }
        cout << '\n';
    }

    return 0;
}