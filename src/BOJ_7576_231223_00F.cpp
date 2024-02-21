// title: 백준 7576 토마토 G5
// date: 2023-12-23 T 20:56

#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

struct Pos {
public:
    Pos(int y, int x): x_(x), y_(y) {};
public:
    inline bool is_in_bound(size_t x_min, size_t x_max, size_t y_min, size_t y_max) const { 
        return is_in_x_bound(x_min, x_max) && is_in_y_bound(y_min, y_max); 
    };
    inline bool is_in_x_bound(size_t x_min, size_t x_max) const { return (x_min <= x_ && x_ < x_max); }
    inline bool is_in_y_bound(size_t y_min, size_t y_max) const { return (y_min <= y_ && y_ < y_max); }
public:
    static vector<Pos> get_offsets() {
        vector<Pos> ret { 
            Pos::offset_l(), 
            Pos::offset_r(),
            Pos::offset_u(),
            Pos::offset_d()
        };
        return ret;
    }
    static Pos offset_l() { return Pos( 0, -1); };
    static Pos offset_r() { return Pos( 0, +1); };
    static Pos offset_u() { return Pos(-1,  0); };
    static Pos offset_d() { return Pos(+1,  0); };
    friend Pos operator+(const Pos& l, const Pos& r) {
        return Pos(l.y_ + r.y_, l.x_ + r.x_);
    }
    Pos& operator+=(const Pos& r) {
        y_ += r.y_;
        x_ += r.x_;
    }
public:
    int y_{0}, x_{0};
};

class TomatoCell {
private:
    enum TomatoState { Riped = 1, NotRiped = 0, None = -1 };
public:
    TomatoCell(): pos_(0, 0) {};
    TomatoCell(const TomatoCell& oth): state_(oth.state_), pos_(oth.pos_) {};
public:
    inline bool has_tomato() const { return state_ != None; };
    inline bool is_riped() const { return has_tomato() && state_ == Riped; };
    inline bool is_unriped() const { return has_tomato() && state_ == NotRiped; };
public:
    inline void make_ripe() {
        assert(state_ == NotRiped);
        state_ = Riped;
        return;
    }
public:
    inline void set_pos(int y, int x) { pos_.x_ = x, pos_.y_ = y; };
    inline void set_state(int in_state) { state_ = (TomatoState)in_state; };
public:
    inline Pos pos() const { return pos_; };
    inline int state() const { return state_; };
public:
    vector<Pos> get_adjacent_poss(size_t max_bound_y, size_t max_bound_x) const {
        vector<Pos> ret;
        const auto offsets = Pos::get_offsets();
        for (const auto& offset: offsets)
        {
            auto tpos = pos_ + offset;
            if (tpos.is_in_bound(0, max_bound_x, 0, max_bound_y))
                ret.push_back(tpos);
        }
        return ret;
    }
#ifdef PS_DEBUG
public:
    void print() const {
        cout << state_ << "[" << pos_.y_ << "][" << pos_.x_ << "]";
        return;
    }
#endif //PS_DEBUG 
private:
    TomatoState state_ { None };
    Pos pos_;
};

class Box {
public:
    Box(const int N, const int M): box_(N, vector<TomatoCell>(M)) {
        for (size_t n = 0; n < box_.size(); ++n)
        {
            for (size_t m = 0; m < box_.front().size(); ++m)
            {
                int tstate; cin >> tstate; 
                box_[n][m].set_state(tstate);
                box_[n][m].set_pos(n, m);

                if (box_[n][m].has_tomato()) 
                    tomatos_.push_back(&box_[n][m]);
            }
        }
        return;
    };

    int days_all_ripe() {

        int days_passed = 0;

        while (!is_all_riped())
        {
            vector<TomatoCell> tstate_copy(tomatos_.size());
            for (size_t i = 0; i < tstate_copy.size(); ++i) {
                const auto ttomato = *tomatos_[i];
                tstate_copy[i] = ttomato;
            }

            queue<Pos> to_visit;
            static vector<vector<bool>> visited(size_y(), vector<bool>(size_x(), false));

            for (const auto& tptr: tomatos_) {
                if (visited[tptr->pos().y_][tptr->pos().x_])
                    continue;
                if (tptr->is_riped()) {
                    #ifdef PS_DEBUG
                    cout << ">> Adding riped tomato: ";
                    tptr->print(); cout << "\n";
                    #endif //PS_DEBUG 

                    to_visit.push(tptr->pos());
                    visited[tptr->pos().y_][tptr->pos().x_] = true;
                }
            }

            while(!to_visit.empty()) {
                auto cpos = to_visit.front();
                auto& ctomato = box_[cpos.y_][cpos.x_];
                to_visit.pop();

                for (const auto& adj_pos: ctomato.get_adjacent_poss(size_y(), size_x())) {
                    if (visited[adj_pos.y_][adj_pos.x_])
                        continue;

                    auto& cadj_tomato = box_[adj_pos.y_][adj_pos.x_];

                    // 안익은것만 추가해야함 
                    if (cadj_tomato.is_unriped()) {
                        cadj_tomato.make_ripe(); // 익는 부분
                        //to_visit.push(cadj_tomato.pos());
                        //visited[cadj_tomato.pos().y_][cadj_tomato.pos().x_] = true;
                    }
                }
            }

            days_passed++;

            #ifdef PS_DEBUG
            //cout << "> days_passed :" << days_passed << "\n";
            //print();
            #endif //PS_DEBUG 


            if (!has_changed(tstate_copy)) {
                if (!is_all_riped()) return -1;
                return days_passed - 1;
            }

        }

        return days_passed;
    }

    bool has_changed(const vector<TomatoCell>& tcopy) const {
        for(size_t i = 0; i < tcopy.size(); ++i) {
            if (tomatos_[i]->state() != tcopy[i].state())
            {
                return true;
            }
        }
        return false;
    }


    bool is_all_riped() const {
        for (const auto& tptr: tomatos_) {
            if (!tptr->is_riped()) 
                return false;
        }
        return true;
    }
    inline size_t size_x() const { return box_.front().size(); };
    inline size_t size_y() const { return box_.size(); };

    #ifdef PS_DEBUG
    void print() const {
        for (const auto& l: box_) {
            for(const auto& cell: l) {
                cell.print(); cout << " ";
            }
            cout << "\n";
        }
        return;
    }
    void print_only_tomato() const {
        for (const auto& a: tomatos_) {
            a->print(); cout << "\n";
        }
        cout << "\n";
    }
    #endif //PS_DEBUG 
private:
    vector<vector<TomatoCell>> box_;
    vector<TomatoCell*> tomatos_;
};

auto main() -> int {
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int M; cin >> M; // 가로 칸 [2, 1000]
    int N; cin >> N; // 세로 칸 [2, 1000]

    Box box(N, M);

    #ifdef PS_DEBUG
    cout << "Input Box Test: \n";
    box.print();
    cout << "\n";
    //cout << "Input Tomato Test: \n";
    //box.print_only_tomato();
    #endif //PS_DEBUG 

    cout << box.days_all_ripe();

    return 0;
}