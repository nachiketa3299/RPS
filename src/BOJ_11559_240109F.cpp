// title: 백준 11559 Puyo Puyo G4
// date: 18:22 20:10 (110)
// Failed : 중력 처리를 못하겠음
#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Pos2 {
public:
    Pos2(): v(0), h(0) {}
    Pos2(const int& v, const int& h): v(v), h(h) {}
    Pos2(const Pos2& pos): v(pos.v), h(pos.h) {}
public:
    static std::vector<Pos2> GetOffsets() {
        return std::vector<Pos2> { Pos2(-1, 0), Pos2(+1, 0), Pos2(0, -1), Pos2(0, +1) };
    }
    inline bool IsInBound(const Pos2& min_vh, const Pos2& max_vh) const {
        const bool is_in_v_bound = min_vh.v <= v && v < max_vh.v;
        const bool is_in_h_bound = min_vh.h <= h && h < max_vh.h;
        return is_in_v_bound && is_in_h_bound;
    }
public:
    Pos2 operator+(const Pos2& other) const {
        return Pos2(v + other.v, h + other.h);
    }
    bool operator==(const Pos2& other) const {
        return v == other.v && h == other.h;
    }
    bool operator!=(const Pos2& other) const {
        return !(*this == other);
    }
public:
    int v, h;
};


class Board {
private:
    static constexpr size_t kBoardSize_v = 12;
    static constexpr size_t kBoardSize_h = 6;
    static constexpr size_t kChunkSize = 4;
    enum CellState {
        Empty, Red, Green, Blue, Purple, Yellow
    };
public:
    Board(): cell_states_(kBoardSize_v, vector<CellState>(kBoardSize_h, Empty)) {
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                char tstate; cin >> tstate;
                auto& cb = cell_states_[v][h];
                switch (tstate) {
                    default:
                    case '.': cb = Empty; break;
                    case 'R': cb = Red; break;
                    case 'Y': cb = Yellow; break;
                    case 'G': cb = Green; break;
                    case 'P': cb = Purple; break;
                    case 'B': cb = Blue; break;
                }
            }
        }
    }
    inline size_t size_v() const {
        return cell_states_.size();
    }
    inline size_t size_h() const {
        return cell_states_.front().size();
    }
public:
    vector<Pos2> GetAdjacnetPoses(const Pos2& pivot_pos) const {
        vector<Pos2> ret;
        for (const auto& offset: Pos2::GetOffsets()) {
            const auto& tpos = pivot_pos + offset;
            if (!tpos.IsInBound(Pos2(0, 0), Pos2(size_v(), size_h())))
                continue;
            ret.push_back(tpos);
        }
        return ret;
    }
    size_t GetChainNumber() {

        bool o_has_chain = false;
        bool o_physics_changed = false;
        int o_chain_num = 0;

        do {
            // a) Remove All while possible!
            for (size_t v = 0; v < size_v(); ++v) {
                for (size_t h = 0; h < size_h(); ++h) {
                    const auto& cstate = cell_states_[v][h];
                    if (cstate == Empty)
                        continue;
                    // there's something not empty
                    queue<Pos2> to_visit;
                    vector<vector<bool>> visited(size_v(), vector<bool>(size_h(), false));
                    vector<Pos2> chunk;

                    to_visit.push(Pos2(v, h));
                    visited[to_visit.front().v][to_visit.front().h] = true;
                    chunk.push_back(to_visit.front());

                    while (!to_visit.empty()) {
                        const auto cvisit = to_visit.front(); to_visit.pop();
                        for (const auto& adj_pos: GetAdjacnetPoses(cvisit)) {
                            if (visited[adj_pos.v][adj_pos.h])
                                continue;
                            visited[adj_pos.v][adj_pos.h] = true;
                            const auto& adj_state = cell_states_[adj_pos.v][adj_pos.h];

                            if (adj_state == Empty)
                                continue;
                            if (adj_state != cstate)
                                continue;
                            
                            to_visit.push(adj_pos);
                            chunk.push_back(adj_pos);
                        }
                    }

                    if (chunk.size() < kChunkSize) 
                        continue;
                    // Destroy
                    for_each(chunk.cbegin(), chunk.cend(), [this](const auto& pos) { cell_states_[pos.v][pos.h] = Empty; });

                    if (!o_has_chain) 
                        o_chain_num++;
                    o_has_chain = true;
                }
            }
            // b) Gravity

            do {
                o_physics_changed = false;
                for (size_t v = 0; v < size_v(); ++v) {
                    for (size_t h = 0; h < size_h(); ++h) {
                        auto& cstate = cell_states_[v][h];
                        if (cstate == Empty)
                            continue;
                        
                        if (!(v + 1 < size_v()))
                            continue;
                        
                        if (cell_states_[v + 1][h] != Empty)
                            continue;
                        
                        cell_states_[v + 1][h] = cstate;
                        cstate = Empty;
                        o_physics_changed = true;
                    }
                }
            } while (o_physics_changed);

        } while (o_has_chain || o_physics_changed);
        // c) return chain num

        return o_chain_num;
    }
private:
    vector<vector<CellState>> cell_states_;
#ifdef PS_DEBUG
public:
    void PrintBoard() const {
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                auto& cb = cell_states_[v][h];
                char del;
                switch(cb) {
                    default:
                    case Empty:     del = '.'; break;
                    case Red:       del = 'R'; break;
                    case Yellow:    del = 'Y'; break;
                    case Green:     del = 'G'; break;
                    case Purple:    del = 'P'; break;
                    case Blue:      del = 'B'; break;
                }
                cout << del;
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

    Board board;

    #ifdef PS_DEBUG
    cout << "> Input Test:\n";
    board.PrintBoard();
    #endif //PS_DEBUG 

    cout << board.GetChainNumber();

    #ifdef PS_DEBUG
    cout << "\n> 1 chain Test:\n";
    board.PrintBoard();
    #endif //PS_DEBUG 
    return 0;
}