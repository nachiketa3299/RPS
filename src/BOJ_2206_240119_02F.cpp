// title: 백준 2206 벽 부수고 이동하기 G3
// date: 12:23 13:42
// Failed 또다시 Visited.

#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
#include <string>

using namespace std;
using Pos_t = int;
using Weight_t = int;

constexpr Pos_t kInvalidPos = -1;
constexpr Weight_t kInfiniteWeight = numeric_limits<Weight_t>::max();
constexpr Weight_t kZeroWeight = 0;
constexpr int kPathFindError = -1;

struct Pos2_t {
    Pos_t v = kInvalidPos;
    Pos_t h = kInvalidPos;
    bool operator==(const Pos2_t& other) const {
        return v == other.v && h == other.h;
    }
    Pos2_t operator+(const Pos2_t& other) const {
        return Pos2_t{ v + other.v, h + other.h };
    }
    static vector<Pos2_t> Get_RLUD_Offsets() {
        return vector<Pos2_t> { Pos2_t{-1, 0}, Pos2_t{+1, 0},Pos2_t{0, -1},Pos2_t{0, +1} };
    }
};

class Map {
private:
    enum class CellState {
        Invalid = -1, Path = 0, Wall = 1
    };
    
public:
    Map(size_t v_size, size_t h_size) 
        : cell_states_(v_size + 1, vector<CellState>(h_size + 1, CellState::Invalid))
    {
        for (size_t v = 1; v < size_v(); ++v) {
            string line; cin >> line;
            transform(line.cbegin(), line.cend(), next(cell_states_[v].begin()), [](const auto& c){
                return c == '1' ? CellState::Wall : CellState::Path;
            });
        }
        #ifdef PS_DEBUG
        PrintAdjacentMatrix();
        #endif //PS_DEBUG 
    }
    inline size_t size_v() const {
        return cell_states_.size();
    }
    inline size_t size_h() const {
        return cell_states_.front().size();
    }
    Weight_t BFS_ShortestPath(const Pos2_t& s_pos, const Pos2_t& e_pos)  {
        if (s_pos == e_pos)
            return kZeroWeight;
        static constexpr int max_bc = 1;
        using b_pair = pair<int, Pos2_t>; // break_count, position
        vector<vector<vector<Weight_t>>> distance_by_bc(max_bc + 1, vector<vector<Weight_t>>(size_v(), vector<Weight_t>(size_h(), kInfiniteWeight)));
        vector<vector<vector<bool>>> visited_by_bc(max_bc + 1, vector<vector<bool>>(size_v(), vector<bool>(size_h(), false)));
        queue<b_pair> to_visit;
        int c_bc = 0;

        to_visit.push({c_bc, s_pos});
        distance_by_bc[c_bc][s_pos.v][s_pos.h] = kZeroWeight + 1;
        visited_by_bc[c_bc][s_pos.v][s_pos.h] = true;

        while (!to_visit.empty()) {
            const auto [cv_bc, cv_pos] = to_visit.front();
            to_visit.pop();

            for (const auto& adj_pos: MakeAdjacentPoses(cv_pos)) {
                const auto& adj_state = cell_states_[adj_pos.v][adj_pos.h];
                if (cv_bc < max_bc) {
                    // Can break
                    switch(adj_state) {
                        case CellState::Path:
                            if(visited_by_bc[cv_bc][adj_pos.v][adj_pos.h])
                                continue;
                            visited_by_bc[cv_bc][adj_pos.v][adj_pos.h] = true;
                            distance_by_bc[cv_bc][adj_pos.v][adj_pos.h] = distance_by_bc[cv_bc][cv_pos.v][cv_pos.h] + 1;
                            to_visit.push({cv_bc, adj_pos});
                            break;
                        case CellState::Wall: {
                            const auto n_bc = cv_bc + 1;
                            if(visited_by_bc[n_bc][adj_pos.v][adj_pos.h])
                                continue;
                            visited_by_bc[n_bc][adj_pos.v][adj_pos.h] = true;
                            distance_by_bc[n_bc][adj_pos.v][adj_pos.h] = distance_by_bc[cv_bc][cv_pos.v][cv_pos.h] + 1;
                            to_visit.push({n_bc, adj_pos});
                            break;
                        }
                        default: break;
                    }
                }
                else {
                    // Can't break
                    switch(adj_state) {
                        case CellState::Path:
                            if(visited_by_bc[cv_bc][adj_pos.v][adj_pos.h])
                                continue;
                            visited_by_bc[cv_bc][adj_pos.v][adj_pos.h] = true;
                            distance_by_bc[cv_bc][adj_pos.v][adj_pos.h] = distance_by_bc[cv_bc][cv_pos.v][cv_pos.h] + 1;
                            to_visit.push({cv_bc, adj_pos});
                            break;
                        case CellState::Wall:
                            if(visited_by_bc[cv_bc][adj_pos.v][adj_pos.h])
                                continue;
                            visited_by_bc[cv_bc][adj_pos.v][adj_pos.h] = true;
                            break;
                        default: break;
                    }
                }
            }
        }

        #ifdef PS_DEBUG
        cout << "> NB\n";
        PrintVector(distance_by_bc[0]);
        cout << "> B\n";
        PrintVector(distance_by_bc[1]);
        #endif //PS_DEBUG 

        priority_queue<int, vector<int>, greater<int>> pq;
        for (size_t m = 0; m <= max_bc; ++m)
            pq.push(distance_by_bc[m][e_pos.v][e_pos.h]);
        return pq.top();
    }
    vector<Pos2_t> MakeAdjacentPoses(const Pos2_t pos) {
        vector<Pos2_t> ret;
        for (const auto& offset: Pos2_t::Get_RLUD_Offsets()) {
            const auto candid_pos = pos + offset;
            if (!(1 <= candid_pos.v && candid_pos.v < size_v()))
                continue;
            if (!(1 <= candid_pos.h && candid_pos.h < size_h()))
                continue;
            ret.push_back(candid_pos);
        }
        return ret;
    }
    #ifdef PS_DEBUG
    static void PrintVector(const vector<vector<int>>& vec) {
        cout << "> Printing Vec: \n";
        for (size_t v = 1; v < vec.size(); ++v) {
            for (size_t h = 1; h < vec.front().size(); ++h) {
                const auto& val = vec[v][h];
                switch(val) {
                    case kInfiniteWeight:
                        cout << "INF";
                        break;
                    default:
                        cout << val;
                }
                cout << '\t';
            }
            cout << '\n';
        }
        cout << '\n';
    }
    void PrintAdjacentMatrix() const {
        cout << "> AdjacentMatrix:\n";
        for (size_t v = 1; v < size_v(); ++v) {
            for (size_t h = 1; h < size_h(); ++h) {
                const auto& c_state = cell_states_[v][h];
                switch(c_state) {
                    case CellState::Wall:
                        cout << 'X';
                        break;
                    case CellState::Path:
                        cout << '.';
                        break;
                }
            }
            cout << '\n';
        }
        cout << '\n';
    }
    #endif //PS_DEBUG 

private:
    vector<vector<CellState>> cell_states_;
};

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int N, M; cin >> N >> M;
    const auto& map_v_size = N; // [1, 1'000]
    const auto& map_h_size = M; // [1, 1'000]

    Map graph(map_v_size, map_h_size);

    Pos2_t s_pos{ 1, 1 };
    Pos2_t e_pos{ N, M };
    const auto dist = graph.BFS_ShortestPath(s_pos, e_pos);

    switch(dist) {
        case kInfiniteWeight:
            cout << kPathFindError;
            break;
        default:
            cout << dist;
            break;
    }

    return 0;
}