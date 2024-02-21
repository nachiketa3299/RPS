// title: 백준 10282 해킹 G4
// date: 18:07 18:46 (39)

#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <limits>

using namespace std;

using VertexPos_t = int;
using Weight_t = int; // Should be >= 0
constexpr Weight_t kInfiniteWeight = numeric_limits<Weight_t>::max();
constexpr Weight_t kZeroWeight = 0;


class Graph {
private:
    using GPair_t = pair<Weight_t, VertexPos_t>;
    using PQ_GP_ASC = priority_queue< GPair_t, vector<GPair_t>, greater<GPair_t> >;
public:
    Graph(size_t v_size) 
        : adj_lists_(v_size + 1, vector<GPair_t>())
    { }
    inline size_t size_v() const {
        return adj_lists_.size();
    }
    void AddDirectedEdge(VertexPos_t s_pos, VertexPos_t e_pos, Weight_t weight) {
        adj_lists_[s_pos].push_back(make_pair(weight, e_pos));
    }
    void Dikjstra(VertexPos_t s_pos, vector<Weight_t>& out_distance) {

        PQ_GP_ASC to_visit;

        // Init Queue
        out_distance[s_pos] = kZeroWeight;
        to_visit.push(make_pair(out_distance[s_pos], s_pos));

        while (!to_visit.empty()) {
            const auto [cv_w, cv_pos] = to_visit.top();
            to_visit.pop();
            
            if (cv_w > out_distance[cv_pos])
                continue;

            for (const auto& [adj_w, adj_pos]: adj_lists_[cv_pos]) {
                auto& dist_cache = out_distance[adj_pos];
                const auto dist_new = cv_w + adj_w;

                if (!(dist_new < dist_cache))
                    continue;

                dist_cache = dist_new;
                to_visit.push(make_pair(dist_new, adj_pos));
            }
        }
    }

#ifdef PS_DEBUG
    void PrintAdjacentlist() const {
        cout << "> Printing Adjacent List: \n";
        for (size_t v = 1; v < size_v(); ++v) {
            cout << v << " | ";
            for (const auto& [w, e_pos]: adj_lists_[v])
                cout << "(" << w << ", " << e_pos << ") ";
            cout << '\n';
        }
        cout << '\n';
    }
    static void PrintDistance(const vector<Weight_t>& in_distances) {
        cout << "> Distances: ";
        for (size_t v = 1; v < in_distances.size(); ++v) {
            if (in_distances[v] == kInfiniteWeight)
                cout << "INF";
            else 
                cout << in_distances[v];
            cout << " ";
        }
        cout << '\n';
    }
#endif //PS_DEBUG 

private:
    vector< vector<GPair_t> > adj_lists_;
};

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    size_t test_case_size; cin >> test_case_size; // [1, 100]

    /* TC_LOOP START */ for (size_t tc = 0; tc < test_case_size; ++tc) {

    int n, d, c;
    cin >> n >> d >> c;
    const auto& vertex_size = n;        // [1, 10'000]
    const auto& directed_edge_size = d; // [1, 100'000]
    const auto& start_vertex = c;       // [1, vertex_size]

    Graph graph(vertex_size);

    for (size_t de = 0; de < directed_edge_size; ++de) {
        VertexPos_t a, b; Weight_t s;
        cin >> a >> b >> s;
        // no redundant (a, b) pairs exists
        graph.AddDirectedEdge(b, a, s);
    }

    #ifdef PS_DEBUG
    graph.PrintAdjacentlist();
    #endif //PS_DEBUG 

    vector<Weight_t> shortest_distance_from_start_vertex(vertex_size + 1, kInfiniteWeight);
    graph.Dikjstra(start_vertex, shortest_distance_from_start_vertex);

    #ifdef PS_DEBUG
    Graph::PrintDistance(shortest_distance_from_start_vertex);
    #endif //PS_DEBUG 

    size_t connected_component_size = 0;
    size_t longest_distance = kZeroWeight;

    for (size_t v = 1; v <= vertex_size; ++v) {
        const auto& c_distance = shortest_distance_from_start_vertex[v];
        if (c_distance == kInfiniteWeight)
            continue;
        connected_component_size++;
        if (c_distance > longest_distance) 
            longest_distance = c_distance;
    }

    cout << connected_component_size << " ";
    cout << longest_distance << '\n';

    /* TC_LOOP END */}

    return 0;
}