// title: 백준 2206 벽 부수고 이동하기 G3
// date: 15:26 18:15 169

#define PS_DEBUG
//#undef PS_DEBUG
/*
01000
10000
00000
00000
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <string>
#include <limits>

using namespace std;

using Pos_t = int;
using Weight_t = int;
constexpr Pos_t kInvalidPos = -1;
constexpr Weight_t kZeroWeight = 0;
constexpr Weight_t kInfiniteWeight = numeric_limits<Weight_t>::max();
constexpr Weight_t kPathFindError = -1;

struct Bool {
    bool val = false;
    Bool& operator=(bool other) {
        val = other;
        return *this;
    }
    bool& Get() {
        return val;
    }
};

struct Pos2_t {
    Pos_t v = kInvalidPos;
    Pos_t h = kInvalidPos;
    Pos2_t operator+(const Pos2_t& other) const {
        return Pos2_t{ v + other.v, h + other.h };
    }
    static vector<Pos2_t> GetOffsets() {
        return vector<Pos2_t> { Pos2_t{0, +1}, Pos2_t{0, -1}, Pos2_t{+1, 0}, Pos2_t{-1, 0} };
    }
    vector<Pos2_t> GetAdjacentPoses(const Pos2_t& min_bound, const Pos2_t& max_bound) const {
        vector<Pos2_t> ret;
        for (const auto& offset: GetOffsets()) {
            const auto candid_pos = *this + offset;
            if (!(min_bound.v <= candid_pos.v && candid_pos.v < max_bound.v))
                continue;
            if (!(min_bound.h <= candid_pos.h && candid_pos.h < max_bound.h))
                continue;
            ret.push_back(candid_pos);
        }
        return ret;
    }

};

class MapGraph {
    enum class CellState {
        Invalid = -1, Path = 0, Wall = 1
    };

public:
    MapGraph(size_t map_v_size, size_t map_h_size) 
        : adj_matrix_(map_v_size + 1, vector<CellState>(map_h_size + 1, CellState::Invalid))
    {
        for (size_t v = 1; v < size_v(); ++v) {
            string c_line; cin >> c_line;
            for (size_t h = 1; h < size_h(); ++h) {
                switch(c_line[h - 1]) {
                    case '0':
                        adj_matrix_[v][h] = CellState::Path; break;
                    case '1':
                        adj_matrix_[v][h] = CellState::Wall; break;
                }
            }
        }
        
        #ifdef PS_DEBUG
        PrintAdjacentMatrix();
        #endif //PS_DEBUG 
    }
    inline int size_v() const {
        return adj_matrix_.size();
    }
    inline int size_h() const {
        return adj_matrix_.front().size();
    }

#ifdef PS_DEBUG
    static void PrintDistance(vector< vector<Weight_t> >& vec) {
        cout << ">> Printing Weights:\n";
        for (size_t v = 1; v < vec.size(); ++v) {
            for (size_t h = 1; h < vec[v].size(); ++h) {
                const auto& c_val = vec[v][h];
                if (c_val == kInfiniteWeight)
                    cout << "INF";
                else
                    cout << c_val;
                cout << "\t";
            }
            cout << "\n";
        }
        cout << "\n";
    }
    void PrintAdjacentMatrix() const {
        cout << "> Print Adjacent Matrix:\n";
        for (size_t v = 1; v < size_v(); ++v) {
            for (size_t h = 1; h < size_h(); ++h) {
                const auto& c_state = adj_matrix_[v][h];
                char del;
                switch(c_state) {
                    case CellState::Invalid: del = '='; break;
                    case CellState::Path:    del = '.'; break;
                    case CellState::Wall:    del = 'X'; break;
                }
                cout << del;
            }
            cout << '\n';
        }
        cout << '\n';
    }
#endif //PS_DEBUG 
    template <typename T>
    static T& GetRef(vector< vector<T> >& vec, const Pos2_t& pos) {
        return vec[pos.v][pos.h];
    }

    Weight_t BFS_ShortestPath(const Pos2_t& s_pos, const Pos2_t& e_pos) {
        // (CurrentPos, state: is some wall breaked until reaching this pos?)
        using b_pair = pair<Pos2_t, bool>; 
        // distance_normal[v][h] is s_pos ~ Pos2_t{v, h} distance "with no break"
        vector< vector<Weight_t> > distance_normal(size_v(), vector<Weight_t>(size_h(), kInfiniteWeight));
        // distance_breaked[v][h] is s_pos ~ Pos2_t{v, h} distance "with 1 break"
        vector< vector<Weight_t> > distance_breaked(size_v(), vector<Weight_t>(size_h(), kInfiniteWeight));
        // custom Bool to use GetRef func 
        vector< vector<Bool> > visited_normal(size_v(), vector<Bool>(size_h()));
        vector< vector<Bool> > visited_breaked(size_v(), vector<Bool>(size_h()));

        queue<b_pair> to_visit;
        to_visit.push(make_pair(s_pos, false)); // s_pos & e_pos are always "Path"

        // Init BFS Condition
        GetRef(distance_normal, s_pos) = kZeroWeight + 1;
        GetRef(visited_normal, s_pos) = true;

        while (!to_visit.empty()) {
            const auto [cv_pos, already_breaked] = to_visit.front();
            to_visit.pop();

            for (const auto& adj_pos: cv_pos.GetAdjacentPoses(Pos2_t{1, 1}, Pos2_t{size_v(), size_h()})) {
                const auto& adj_state = GetRef(adj_matrix_, adj_pos);

                switch(adj_state) {
                    case CellState::Path: {
                        if (already_breaked) {
                            // Can't break more
                            if (GetRef(visited_breaked, adj_pos).Get())
                                continue;
                            GetRef(visited_breaked, adj_pos) = true;
                            GetRef(distance_breaked, adj_pos) = GetRef(distance_breaked, cv_pos) + 1;
                            to_visit.push(make_pair(adj_pos, true));
                        }
                        else /*!already breaked*/{
                            if (GetRef(visited_normal, adj_pos).Get())
                                continue;
                            GetRef(visited_normal, adj_pos) = true;
                            GetRef(distance_normal, adj_pos) = GetRef(distance_normal, cv_pos) + 1;
                            to_visit.push(make_pair(adj_pos, false));
                        }
                        break;
                    }
                    case CellState::Wall: {
                        if (already_breaked) {
                            // Can't break more
                            if (GetRef(visited_breaked, adj_pos).Get())
                                continue;
                            GetRef(visited_breaked, adj_pos) = true;
                        }
                        else /*!already breaked*/ {
                            // break!
                            if (GetRef(visited_normal, adj_pos).Get())
                                continue;
                            GetRef(visited_normal, adj_pos) = true;
                            if (GetRef(visited_breaked, adj_pos).Get())
                                continue;
                            GetRef(visited_breaked, adj_pos) = true;
                            GetRef(distance_breaked, adj_pos) = GetRef(distance_normal, cv_pos) + 1;
                            to_visit.push(make_pair(adj_pos, true));
                        }
                        break;
                    }

                    default:
                    case CellState::Invalid:
                        cout << "> ERROR!\n";
                        return kInfiniteWeight;
                }
            }
        }
        #ifdef PS_DEBUG
        cout << ">> Normal:\n";
        PrintDistance(distance_normal);
        cout << ">> Crashed:\n";
        PrintDistance(distance_breaked);
        #endif //PS_DEBUG 

        return min(GetRef(distance_normal, e_pos), GetRef(distance_breaked, e_pos));
    }

public:
    vector< vector<CellState> > adj_matrix_;
};

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int N, M; 
    cin >> N >> M;
    const int& map_v_size = N; // [1, 1'000]
    const int& map_h_size = M; // [1, 1'000]

    MapGraph graph(map_v_size, map_h_size);
    const auto& distance = graph.BFS_ShortestPath(Pos2_t{ 1, 1 }, Pos2_t{ N, M });

    if (distance == kInfiniteWeight) 
        cout << kPathFindError;
    else
        cout << distance;

    return 0;
}