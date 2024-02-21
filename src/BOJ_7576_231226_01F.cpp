// title: 백준 7576 토마토 (시간 초과)
// date: 2023-12-26 13:04

#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>

#ifdef PS_DEBUG
#include <string>
#endif //PS_DEBUG 

using namespace std;
struct Pos {
public:
    Pos(): v_(0), h_(0) {};
    Pos(const int& v, const int& h): v_(v), h_(h) {};
public:
    vector<Pos> get_adj_offsets(const Pos& vh_min, const Pos& vh_max) const {
        vector<Pos> ret;
        vector<Pos> offsets {
            Pos::offset_d(), Pos::offset_l(), Pos::offset_r(), Pos::offset_u()
        };
        for (const auto& offset: offsets) {
            const auto tpos = *this + offset;
            if (!tpos.is_in_bound(vh_min, vh_max))
                continue;
            ret.push_back(tpos);
        }
        return ret;
    }
    Pos& operator+=(const Pos& r) {
        v_ += r.v_;
        h_ += r.h_;
        return *this;
    }
    Pos operator+(const Pos& r) const {
        return Pos(v_ + r.v_, h_ + r.h_);
    }
    inline bool is_in_bound(const Pos& vh_min, const Pos& vh_max) const {
        return is_in_min_bound(vh_min) && is_in_max_bound(vh_max);
    }
    inline bool is_in_min_bound(const Pos& vh_min) const {
        return vh_min.v_ <= v_ && vh_min.h_ <= h_;
    }
    inline bool is_in_max_bound(const Pos& vh_max) const {
        return v_ < vh_max.v_ && h_ < vh_max.h_;
    }
public:
    static Pos offset_l() { return Pos( 0, -1); };
    static Pos offset_r() { return Pos( 0, +1); };
    static Pos offset_u() { return Pos(-1,  0); };
    static Pos offset_d() { return Pos(+1,  0); };
#ifdef PS_DEBUG
    void print() const {
        cout << "[" << v_ << "][" << h_ << "]";
    }
#endif //PS_DEBUG 
public:
    int v_;
    int h_;
};

namespace Tomato {

class Cell {
private:
    enum Tomato_State {
        Empty = -1, Unriped = 0, Riped = 1
    };
public:
    Cell(): pos_(Pos()), state_(Empty) {};
    Cell(const Pos& pos, int state): pos_(pos), state_((Tomato_State)state) {};
    inline bool is_empty() const { return state_ == Empty; };
    inline bool is_unriped() const { return state_ == Unriped; };
    inline bool is_riped() const { return state_ == Riped; };
    inline void makd_ripe() { state_ = Riped; };
public:
    inline const Pos& pos() const { return pos_; };
#ifdef PS_DEBUG
    void print(bool print_pos) const {
        string delimeter;
        switch(state_) {
            default:
            case Empty: delimeter = "X"; break;
            case Unriped: delimeter = "O"; break;
            case Riped: delimeter = "R"; break;
        }

        cout << delimeter;

        if (print_pos) {
            pos_.print();
            cout << " ";
        }
    }
#endif //PS_DEBUG 
private:
    Pos pos_;
    Tomato_State state_;
};

class Box {
public:
    Box(const int& v, const int& h): cells_(v, vector<Cell>(h)) {
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                int tstate; cin >> tstate;
                cells_[v][h] = Cell(Pos(v, h), tstate);
            }
        }
    };

    int get_days_to_ripe() {

        queue<Cell*> riped_ptrs; // SEED to start BFS
        for (auto& l: cells_) {
            for (auto& cell: l) {
                if (cell.is_riped())
                    riped_ptrs.push(&cell);
            }
        }

        static vector<vector<bool>> visited(size_v(), vector<bool>(size_h(), false));
        static vector<vector<int>> days_to_ripe(size_v(), vector<int>(size_h(), numeric_limits<int>::min()));

        while (!riped_ptrs.empty()) {

            auto cseed = riped_ptrs.front(); riped_ptrs.pop();
            const auto& cseed_pos = cseed->pos();
            visited[cseed_pos.v_][cseed_pos.h_] = true;
            days_to_ripe[cseed_pos.v_][cseed_pos.h_] = 0;

            queue<Cell*> to_visit_ptrs; 
            to_visit_ptrs.push(cseed);

            while(!to_visit_ptrs.empty()) {
                const auto cseed = to_visit_ptrs.front(); to_visit_ptrs.pop();
                const auto& cseed_pos = cseed->pos();

                if (cseed->is_unriped())
                    continue;

                for (auto& adj_ptr: get_adj_ptrs(cseed)) {
                    const auto& cpos = adj_ptr->pos();

                    // 주변 비어있는 거면 생각할 필요도 없이 PASS
                    if (adj_ptr->is_empty())
                        continue;

                    // 주변이 익지 않은 녀석
                    else if (adj_ptr->is_unriped()) {
                        adj_ptr->makd_ripe(); // 익게 만들고
                        visited[cpos.v_][cpos.h_] = true; // 방문 처리
                        days_to_ripe[cpos.v_][cpos.h_] = days_to_ripe[cseed_pos.v_][cseed_pos.h_] + 1;
                        to_visit_ptrs.push(adj_ptr);
                    }

                    // 주변이 익은 녀석
                    else if (adj_ptr->is_riped()) {
                        // 지금 처음 방문하는 거면 아무것도 할 필요 없음
                        if (!visited[cpos.v_][cpos.h_])
                            continue;

                        // 만약 방문 기록이 있다? (다른 시드에서 ripe 처리가 된 녀석)
                        if (visited[cpos.v_][cpos.h_]) {
                            if (days_to_ripe[cpos.v_][cpos.h_] > days_to_ripe[cseed_pos.v_][cseed_pos.h_] + 1) {
                                days_to_ripe[cpos.v_][cpos.h_] = days_to_ripe[cseed_pos.v_][cseed_pos.h_] + 1;
                                to_visit_ptrs.push(adj_ptr);
                            }
                        }
                    }
                }
            }

            #ifdef PS_DEBUG
                for (const auto& l: days_to_ripe) {
                    for (const auto& day: l) {
                        if (day < 0)
                            cout << "X";
                        else
                            cout << day;
                        cout << " ";
                    }
                    cout << "\n";
                }
                cout << "\n";
            #endif //PS_DEBUG 
        }

        auto max_days = 0;
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                if (cells_[v][h].is_unriped())
                    return -1;
                max_days = max(days_to_ripe[v][h], max_days);
            }
        }
        return max_days;
    }
public:
    vector<Cell*> get_adj_ptrs(const Cell* riped_ptr) {
        vector<Cell*> ret;
        const auto& crpos = riped_ptr->pos();
        const auto& adj_poss = crpos.get_adj_offsets(Pos(0, 0), Pos(size_v(), size_h()));
        for (const auto& adj_pos: adj_poss) {
            auto& adj_cell = cells_[adj_pos.v_][adj_pos.h_];
            ret.push_back(&adj_cell);
        }
        return ret;
    }
    inline bool is_all_riped() const {
        for (const auto& l: cells_) {
            for (const auto& cell: l) {
                if (cell.is_unriped())
                    return false;
            }
        }
        return true;
    }
    inline size_t size_v() const { return cells_.size(); };
    inline size_t size_h() const { return cells_.front().size(); };
#ifdef PS_DEBUG
public:
    void print(bool print_pos) const {
        for (const auto& l: cells_) {
            for (const auto& cell: l) {
                cell.print(print_pos);
            }
            cout << "\n";
        }
        cout << "\n";
    }
#endif //PS_DEBUG 
private:
    vector<vector<Cell>> cells_;
};


}; // namespace Tomato

auto main() -> int {
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int M; cin >> M; const int& h = M;
    int N; cin >> N; const int& v = N;
    Tomato::Box box(v, h);
#ifdef PS_DEBUG
    cout << "> Input Test(box, #1)\n";
    box.print(true);
    cout << "> Input Test(box, #2)\n";
    box.print(false);
    cout << "\n";
#endif //PS_DEBUGi 
    
    cout << box.get_days_to_ripe();
    return 0;
}