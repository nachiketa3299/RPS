// title: πÈ¡ÿ 4485 ≥Ïªˆ ø ¿ª ¿‘¿∫ æ÷∞° ¡©¥Ÿ¡ˆ? G4
// date: 18:53 19:39 (46)
#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <utility>
#include <queue>

using namespace std;

using Weight_t = int;
using VertexPos_t = int;
constexpr Weight_t kZeroWeight = 0;
constexpr Weight_t kInfiniteWeight = numeric_limits<Weight_t>::max();

#ifdef PS_DEBUG
void PrintGraph(const vector< vector<Weight_t> >& graph) {
    cout << "> Graph: \n";
    for (size_t v = 0; v < graph.size(); ++v) {
        for (size_t h = 0; h < graph[v].size(); ++h) {
            cout << graph[v][h] << " ";
        }
        cout << '\n';
    }
    cout << '\n';
}
#endif //PS_DEBUG 

struct Pos2_t {
    VertexPos_t v = 0;
    VertexPos_t h = 0;
    static vector<Pos2_t> GetAdjacentOffsets() {
        return vector<Pos2_t>{ {-1, 0}, {+1, 0}, {0, -1}, {0, +1} };
    }
    Pos2_t operator+(const Pos2_t& other) const {
        return Pos2_t{ v + other.v, h + other.h };
    }
    vector<Pos2_t> GetAdjacentPoses(VertexPos_t min_bound, VertexPos_t max_bound) const {
        vector<Pos2_t> ret;
        for (const auto& offset: GetAdjacentOffsets()) {
            const auto c_pos = *this + offset;

            if (!(min_bound <= c_pos.v && c_pos.v < max_bound))
                continue;
            if (!(min_bound <= c_pos.h && c_pos.h < max_bound))
                continue;
            
            ret.push_back(c_pos);
        }
        return ret;
    }
};

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int N; cin >> N;
    auto tc_num = 1;

    while (N != 0) {
        vector< vector<Weight_t> > graph(N, vector<Weight_t>(N, kZeroWeight));

        for (size_t v = 0; v < N; ++v)
            for (size_t h = 0; h < N; ++h)
                cin >> graph[v][h];

        Pos2_t start_vertex{ 0, 0 };
        vector< vector<Weight_t> > distances(N, vector<Weight_t>(N, kInfiniteWeight));

        using g_pair_t = pair<Weight_t, Pos2_t>;
        static const auto pred = [](const g_pair_t& l, const g_pair_t& r) { return l.first > r.first; };
        static const auto get_w = [](vector< vector<Weight_t> >& distance, const Pos2_t& pos)->Weight_t&{ return distance[pos.v][pos.h];};
        using PQ_GP_ASC = priority_queue< g_pair_t, vector<g_pair_t>, decltype(pred)>;

        PQ_GP_ASC to_visit(pred);

        get_w(distances, start_vertex) = get_w(graph, start_vertex);
        to_visit.push(make_pair(get_w(distances, start_vertex), start_vertex));

        while (!to_visit.empty()) {
            const auto [cv_w, cv_pos] = to_visit.top();
            to_visit.pop();

            if (cv_w > get_w(distances, cv_pos))
                continue;

            for (const auto& adj_pos: cv_pos.GetAdjacentPoses(0, N)) {
                const auto& adj_w = get_w(graph, adj_pos);

                auto& distance_cache = get_w(distances, adj_pos);
                const auto& distance_new = cv_w + adj_w;

                if (!(distance_new < distance_cache))
                    continue;

                distance_cache = distance_new;
                to_visit.push(make_pair(distance_new, adj_pos));
            }
        }

        cout << "Problem " << tc_num++ << ": ";
        cout << get_w(distances, Pos2_t{ N - 1, N - 1 }) << "\n";

        cin >> N;
    }


    return 0;
}