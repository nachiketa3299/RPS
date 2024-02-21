// title: 백준 1600 말이 되고픈 원숭이 G3
// date: 21:09 21:57 (48) 23:54 12:18 (36) = 84
// 왜 어렵다고 생각했지?

#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <limits>
#include <array>

using namespace std;

using Pos_t = int;
using Weight_t = int;

constexpr Pos_t kInvalidPos = -1;
constexpr Weight_t kInfiniteWeight = numeric_limits<Weight_t>::max();
constexpr Weight_t kZeroWeight = 0;
constexpr int kPathFindError = -1;

struct Pos2_t {
    Pos_t v{ kInvalidPos };
    Pos_t h{ kInvalidPos };
    Pos2_t operator+(const Pos2_t& other) const {
        return Pos2_t{ v + other.v, h + other.h };
    }
    static vector<Pos2_t> Get_RLUD_Offsets() {
        return vector<Pos2_t> {
            Pos2_t{-1, 0}, Pos2_t{+1, 0}, Pos2_t{0, -1}, Pos2_t{0, +1}
        };
    }
    static vector<Pos2_t> Get_Knight_Offsets() {
        return vector<Pos2_t> {
            Pos2_t{+2, +1}, Pos2_t{+1, +2},
            Pos2_t{-1, +2}, Pos2_t{-2, +1},
            Pos2_t{-2, -1}, Pos2_t{-1, -2},
            Pos2_t{+2, -1}, Pos2_t{+1, -2}
        };
    }

};

class Board {
    enum class CellState {
        Invalid = -1, Path = 0, Wall = 1
    };
    inline friend istream& operator>>(istream& is, CellState& state) {
        int int_state; cin >> int_state;
        state = static_cast<CellState>(int_state);
        return is;
    }

public:

    Board(size_t v_size, size_t h_size) 
        : cell_states_(v_size, vector<CellState>(h_size, CellState::Invalid))
    {
        // Input board
        for (size_t v = 0; v < size_v(); ++v)
            for (size_t h = 0; h < size_h(); ++h)
                cin >> cell_states_[v][h];
    }
    inline size_t size_v() const {
        return cell_states_.size();
    }
    inline size_t size_h() const {
        return cell_states_.front().size();
    }
public:
    Weight_t BFS_ShortestPath(const Pos2_t& s_pos, const Pos2_t& e_pos, int move_count_max) const {
        vector<vector<vector<Weight_t>>> distance_by_move(move_count_max + 1, vector<vector<Weight_t>>(size_v(), vector<Weight_t>(size_h(), kInfiniteWeight)));
        vector<vector<vector<bool>>> visited_by_move(move_count_max + 1, vector<vector<bool>>(size_v(), vector<bool>(size_h(), false)));
        auto c_move_count = 0;

        using m_pair = pair<int, Pos2_t>; // move count & position
        
        queue<m_pair> to_visit;
        to_visit.push({c_move_count, s_pos});
        distance_by_move[c_move_count][s_pos.v][s_pos.h] = kZeroWeight;
        visited_by_move[c_move_count][s_pos.v][s_pos.h] = true;

        while (!to_visit.empty()) {
            const auto [cv_mc, cv_pos] = to_visit.front();
            to_visit.pop();

            for (const auto& n_adj_pos: MakeAdjacentPoses(cv_pos, Pos2_t::Get_RLUD_Offsets())) {
                if (visited_by_move[cv_mc][n_adj_pos.v][n_adj_pos.h])
                    continue;

                visited_by_move[cv_mc][n_adj_pos.v][n_adj_pos.h] = true;

                if (cell_states_[n_adj_pos.v][n_adj_pos.h] == CellState::Wall)
                    continue;

                distance_by_move[cv_mc][n_adj_pos.v][n_adj_pos.h] = distance_by_move[cv_mc][cv_pos.v][cv_pos.h] + 1;
                to_visit.push({cv_mc, n_adj_pos});
            }

            if (!(cv_mc < move_count_max))
                continue;

            const auto n_mc = cv_mc + 1;

            for (const auto& k_adj_pos: MakeAdjacentPoses(cv_pos, Pos2_t::Get_Knight_Offsets())) {
                if (visited_by_move[n_mc][k_adj_pos.v][k_adj_pos.h])
                    continue;


                visited_by_move[n_mc][k_adj_pos.v][k_adj_pos.h] = true;

                if (cell_states_[k_adj_pos.v][k_adj_pos.h] == CellState::Wall)
                    continue;

                distance_by_move[n_mc][k_adj_pos.v][k_adj_pos.h] = distance_by_move[cv_mc][cv_pos.v][cv_pos.h] + 1;

                to_visit.push({n_mc, k_adj_pos});
            }
        }

        priority_queue<int, vector<int>, greater<int>> pq;
        for (int m = 0; m <= move_count_max; ++m)
            pq.push(distance_by_move[m][e_pos.v][e_pos.h]);
        return pq.top();
    }

    vector<Pos2_t> MakeAdjacentPoses(const Pos2_t& c_pos, const vector<Pos2_t>& offsets) const {
        vector<Pos2_t> ret;
        for (const auto& offset: offsets) {
            const auto candid_pos = c_pos + offset;
            if (!(0 <= candid_pos.v && candid_pos.v < size_v()))
                continue;
            if (!(0 <= candid_pos.h && candid_pos.h < size_h()))
                continue;
            ret.push_back(candid_pos);
        }
        return ret;
    }

private:
    vector< vector<CellState> > cell_states_;
};

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int K; cin >> K;
    int W, H; cin >> W >> H;

    const auto& move_count = K;   // [0, 30]
    const auto& board_v_size = H; // [1, 200]
    const auto& board_h_size = W; // [1, 200]

    Board board(board_v_size, board_h_size);
    Pos2_t s_pos { 0, 0 };
    Pos2_t e_pos { board_v_size - 1, board_h_size - 1 };

    const auto dist = board.BFS_ShortestPath(s_pos, e_pos, move_count);
    if (dist == kInfiniteWeight)
        cout << kPathFindError;
    else
        cout << dist;

    return 0;
}