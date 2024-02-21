// title: 백준 10473 인간 대포 G2
// date: 20:09 21:25 (85)
#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <limits>
#include <cmath>
#include <iomanip>

using namespace std;
using Pos_t = float;
using Distance_t = float;
using Weight_t = float; // time
constexpr Weight_t kInfiniteWeight = numeric_limits<Weight_t>::max();
constexpr Weight_t kZeroWeight = 0;

struct Pos2_t {
    Pos_t x = 0.f;
    Pos_t y = 0.f;
    inline static Distance_t GetDistanceBetween(const Pos2_t& s_pos, const Pos2_t& e_pos) {
        return sqrt(pow((s_pos.x - e_pos.x), 2) + pow((s_pos.y - e_pos.y), 2));
    }

};

class MapGraph {
private:
    using g_pair = pair<Weight_t, Pos_t>;
    using PQ_GP_ASC = priority_queue< g_pair, vector<g_pair>, greater<g_pair> >;
    static constexpr float kHumanSpeed = 5.f;
    static constexpr float kCannonRadius = 50.f;
    static constexpr float kCannonTime = 2.f;
public:
    MapGraph(size_t cannon_count, const Pos2_t& start_pos, const Pos2_t& end_pos)
        : vertices_(cannon_count + 2)
        , adj_lists_(cannon_count + 2)
    {
        // Init vertices
        for (size_t i = 0; i < cannon_count + 2; ++i) {
            if (i == 0)
                vertices_[i] = start_pos;
            else if (i == cannon_count + 2 - 1)
                vertices_[i] = end_pos;
            else
            {
                auto& [cannon_x, cannon_y] = vertices_[i];
                cin >> cannon_x >> cannon_y;
            }
        }
        // Build Adj lists
        for (size_t u = 0; u < size_v(); ++u) {
            for (size_t v = 0; v < size_v(); ++v) {

                if (u == v)
                    continue;

                const auto& s_pos = vertices_[u];
                const auto& e_pos = vertices_[v];
                const auto& total_dist = Pos2_t::GetDistanceBetween(s_pos, e_pos);

                const auto pure_walk_time = total_dist / kHumanSpeed;
                adj_lists_[u].push_back(make_pair(pure_walk_time, v));

                if (!is_cannon(u))
                    continue;
                
                static const auto& cannon_dist = kCannonRadius; 
                const auto& to_walk_dist = abs(total_dist - cannon_dist);

                const auto& walk_time = to_walk_dist / kHumanSpeed;
                static const auto& cannon_time = kCannonTime;
                adj_lists_[u].push_back(make_pair(walk_time + cannon_time, v));
            }
        }
    }
    bool is_cannon(Pos_t pos) const {
        return pos != 0 && pos != size_v() - 1;
    }
    inline size_t size_v() const {
        return vertices_.size();
    }
    inline Pos_t start_v() const {
        return 0;
    }
    inline Pos_t end_v() const {
        return size_v() - 1;
    }
    void Dijkstra(vector<Weight_t>& out_distance) {
        PQ_GP_ASC to_visit;

        out_distance[start_v()] = 0;
        to_visit.push(make_pair(0, start_v()));

        while (!to_visit.empty()) {
            const auto [cv_w, cv_v] = to_visit.top();
            to_visit.pop();

            if (cv_w > out_distance[cv_v])
                continue;

            for (const auto& [adj_w, adj_v]: adj_lists_[cv_v]) {
                auto& dist_cache = out_distance[adj_v];
                const auto dist_new = cv_w + adj_w;

                if (!(dist_new < dist_cache))
                    continue;

                dist_cache = dist_new;
                to_visit.push(make_pair(dist_new, adj_v));
            }
        }
    }
#ifdef PS_DEBUG
public:
    void Print() const {
        cout << "> Vertices:\n";
        for (size_t v = 0; v < size_v(); ++v) {

            cout << v << "[";
            cout <<  vertices_[v].x << ", " << vertices_[v].y;
            cout << "] ";
        }
        cout << "\n> Adjacent Lists:\n";
        for (size_t v = 0; v < size_v(); ++v) {
            cout << v << " | ";
            for (const auto& [time, pos]: adj_lists_[v]) {
                cout << "(";
                cout << time << ", " << pos;
                cout << ") ";
            }
            cout << '\n';
        }
        cout << '\n';
    }
#endif //PS_DEBUG 

private:
    vector<Pos2_t> vertices_;
    vector< vector<g_pair> > adj_lists_;
};

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    float cx, cy; cin >> cx >> cy; // [0, 500]
    float dx, dy; cin >> dx >> dy; // [0, 500]
    int cannon_count; cin >> cannon_count; // [0, 100]


    const Pos2_t kStartPos {cx, cy};
    const Pos2_t kEndPos {dx, dy};
    MapGraph graph(cannon_count, kStartPos, kEndPos);

    #ifdef PS_DEBUG
    graph.Print();
    #endif //PS_DEBUG 

    vector<Weight_t> distances(graph.size_v(), kInfiniteWeight);
    graph.Dijkstra(distances);
    cout << distances[graph.end_v()];

    return 0;
}