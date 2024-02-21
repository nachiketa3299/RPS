// title: 백준 11724 연결 요소의 개수 S2
// date: 2023-12-29 T 15:32 16:25 (53)

#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>

using namespace std;

struct Edge {
public:
    Edge() {};
    size_t u_{0};
    size_t v_{0};
};

class Graph {
public:
    using NodeIndexType = size_t;
public:
    Graph(const int& vertices_count, const int& edges_count): vertices_count_(vertices_count), edges_(edges_count), connected_compenets_count_(0) {
        for_each(edges_.begin(), edges_.end(), [](auto& edges) { cin >> edges.u_ >> edges.v_; });
        initialize();
    }
public:
    inline size_t connected_components_count() const { return connected_compenets_count_; };
private:
    void initialize() {
        // make adjacent list
        vector<vector<NodeIndexType>> adj_list(vertices_count_ + 1, vector<NodeIndexType>());
        for (const auto& edge: edges_) {
            adj_list[edge.u_].push_back(edge.v_);
            adj_list[edge.v_].push_back(edge.u_);
        }

        static deque<bool> visited(vertices_count_ + 1, false);

        for (NodeIndexType seed_vertex = 1; seed_vertex <= vertices_count_; ++seed_vertex) {

            const bool& is_seed_vertex_visited = visited[seed_vertex];
            if (is_seed_vertex_visited) {
                continue;
            }

            // == Seed vertex not visited == 
            queue<NodeIndexType> to_visit;
            to_visit.push(seed_vertex); 
            visited[to_visit.front()] = true;

            while (!to_visit.empty()) {
                const auto cvisit = to_visit.front(); to_visit.pop();
                const auto& cadj_list = adj_list[cvisit];

                for (const auto& adj_v: cadj_list) {
                    auto& is_adj_vertex_visited = visited[adj_v];

                    if (is_adj_vertex_visited) {
                        continue;
                    }
                    is_adj_vertex_visited = true;
                    to_visit.push(adj_v);
                }
            }

            connected_compenets_count_++;
        }


    }
private:
    size_t connected_compenets_count_;
    size_t vertices_count_;
    vector<Edge> edges_;
#ifdef PS_DEBUG
public:
    void print_edges() const {
        cout << "> Edge Input Test:\n";
        for (const auto& edge: edges_)
            cout << edge.u_ << " " << edge.v_ << "\n";
        cout << "\n";
    }
#endif //PS_DEBUG 
};

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int N; cin >> N; 
    int M; cin >> M; 

    const int& vertices_count = N; // [1, 1e3]
    const int& edges_count = M;    // [0, N(N-1)/2]

    Graph graph(vertices_count, edges_count);

    cout << graph.connected_components_count();

    return 0;
}