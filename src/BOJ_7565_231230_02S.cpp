// title: 백준 7576 토마토 G5
// date: 2023-12-30 T 20:02 20:49 (47) 21:57 23:13 (63)

#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;
typedef int BOOL;
#define TRUE 1
#define FALSE 0

struct Pos {
public:
    Pos(): v_(0), h_(0) {}
    Pos(const int& v, const int& h): v_(v), h_(h) {};
public:
    vector<Pos> get_adj_poss(const Pos& min_vh, const Pos& max_vh) const {
        vector<Pos> ret;
        for (const auto& offset: get_offsets()) {
            const Pos tpos = *this + offset;

            if (!tpos.is_in_bound(min_vh, max_vh))
                continue;
            
            ret.push_back(tpos);
        }
        return ret;
    }
    bool is_in_bound(const Pos& min_vh, const Pos& max_vh) const {
        const bool is_in_v_bound = min_vh.v_ <= v_ && v_ < max_vh.v_;
        const bool is_in_h_bound = min_vh.h_ <= h_ && h_ < max_vh.h_;
        return is_in_v_bound && is_in_h_bound;
    }
    Pos operator+(const Pos& r) const { return Pos(v_ + r.v_, h_ + r.h_); };
public:
    int v_; // vertical index
    int h_; // horizontal index
private:
    static vector<Pos> get_offsets() { return vector<Pos>{ offset_l(), offset_r(), offset_u(), offset_d() }; }
    static Pos offset_l() { return Pos( 0, -1); }
    static Pos offset_r() { return Pos( 0, +1); }
    static Pos offset_u() { return Pos(-1,  0); }
    static Pos offset_d() { return Pos(+1,  0); }
#ifdef PS_DEBUG
public:
    void print() const { cout << "[" << v_ << "][" << h_ << "]"; }
#endif //PS_DEBUG 
};

template <typename T>
T& get_pos(vector<vector<T>>& vec, const Pos& pos) { return vec[pos.v_][pos.h_]; }

namespace Tomato {

enum State {
    Empty = -1, Unriped = 0, Riped = 1
};

class Box {
public:
    Box(const int& size_v, const int& size_h): state_(size_v, vector<State>(size_h)) {
    };
    void set_state_at(const Pos& pos, const State& state) {
        state_[pos.v_][pos.h_] = state;
    }
    int days_to_ripe() {
        vector<vector<BOOL>> visited(size_v(), vector<BOOL>(size_h(), FALSE));
        vector<vector<int>> r_days(size_v(), vector<int>(size_h(), numeric_limits<int>::min()));
        queue<Pos> to_visit;

        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                if (state_[v][h] != Riped)
                    continue;
                
                visited[v][h] = TRUE;
                r_days[v][h] = 0;
                to_visit.push(Pos(v, h));
            }
        }

        while(!to_visit.empty()) {
            const Pos c_pos = to_visit.front();
            to_visit.pop();

            for (const auto& adj_pos: c_pos.get_adj_poss(min_vh(), max_vh())) {
                if (get_pos(state_, adj_pos) == Empty)
                    continue;

                if (get_pos(visited, adj_pos)) {
                    get_pos(r_days, adj_pos) = min(get_pos(r_days, c_pos) + 1, get_pos(r_days, adj_pos));
                    continue;
                }

                get_pos(state_, adj_pos) = Riped;
                get_pos(visited, adj_pos) = TRUE;
                get_pos(r_days, adj_pos) = get_pos(r_days, c_pos) + 1;
                to_visit.push(adj_pos);
            }
        }

        #ifdef PS_DEBUG
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                if (r_days[v][h] < 0)
                    cout << 'X';
                else
                    cout << r_days[v][h];
                cout << " ";
            }
            cout << "\n";
        }
        cout << "\n";
        #endif //PS_DEBUG 

        #define CANT_RIPE_ALL -1
        int max_days = numeric_limits<int>::min();
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                if (state_[v][h] == Unriped)
                    return CANT_RIPE_ALL;
                
                if (state_[v][h] == Empty)
                    continue;

                max_days = max(r_days[v][h], max_days);
            }
        }
        #undef CANT_RIPE_ALL

        return max_days;
    }
public:
    inline Pos min_vh() const { return Pos(0, 0); };
    inline Pos max_vh() const { return Pos(size_v(), size_h()); };
    inline size_t size_v() const { return state_.size(); };
    inline size_t size_h() const { return state_.front().size(); };
private:
    vector<vector<State>> state_;
#ifdef PS_DEBUG
public:
    void print(const bool& print_pos) {
        char del;
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                const auto& ctomato = state_[v][h];
                switch(ctomato) {
                    default:
                    case Empty:     del = 'X'; break;
                    case Unriped:   del = 'U'; break;
                    case Riped:     del = 'R'; break;
                }

                cout << del;

                if (print_pos) 
                    cout << "[" << v << "][" << h << "] ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
#endif //PS_DEBUG 
};

istream& operator>>(istream& is, State& state) {
    int int_state; is >> int_state;
    assert(int_state == -1 || int_state == 0 || int_state == 1);
    state = (State)int_state;
    return is;
}

}; // namespace Tomato

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int M, N; cin >> M >> N;
    const int& box_size_v = N; // [2, 1e3]
    const int& box_size_h = M; // [2, 1e3]

    Tomato::Box box(box_size_v, box_size_h);
    for (size_t v = 0; v < box.size_v(); ++v) {
        for (size_t h = 0; h < box.size_h(); ++h) {
            Tomato::State tstate; cin >> tstate;
            box.set_state_at(Pos(v, h), tstate);
        }
    }

    cout << box.days_to_ripe();

    return 0;
}