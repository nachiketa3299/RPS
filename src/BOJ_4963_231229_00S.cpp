// title: 백준 4963 섬의 개수 S2
// date: 2023-12-29 T 16:39 17:46

#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Map;

struct Pos {
public:
    Pos(): v_(0), h_(0) {};
    Pos(const int& v, const int& h): v_(v), h_(h) {};
public:
    inline bool is_in_bound(const Pos& min_vh, const Pos& max_vh) const {
        const bool is_in_v_bound = min_vh.v_ <= v_ && v_ < max_vh.v_;
        const bool is_in_h_bound = min_vh.h_ <= h_ && h_ < max_vh.h_;
        return is_in_v_bound && is_in_h_bound;
    }
    vector<Pos> get_adj_poss(const Pos& min_vh, const Pos& max_vh) const {
        vector<Pos> ret;
        const auto& offsets = Pos::get_offsets();
        for (const auto& offset: offsets) {
            const auto tpos = *this + offset;
            if (!tpos.is_in_bound(min_vh, max_vh))
                continue;
            ret.push_back(tpos);
        }
        return ret;
    }
    Pos operator+(const Pos& r) const { return Pos(v_ + r.v_, h_ + r.h_); };
public:
    static vector<Pos> get_offsets() { 
        return vector<Pos> { 
            Pos::offset_d(), Pos::offset_u(), Pos::offset_l(), Pos::offset_r(),
            Pos::offset_ur(), Pos::offset_ul(), Pos::offset_dl(), Pos::offset_dr()
        }; 
    };
    static Pos offset_l() { return Pos( 0, -1); };
    static Pos offset_r() { return Pos( 0, +1); };
    static Pos offset_u() { return Pos(-1,  0); };
    static Pos offset_d() { return Pos(+1,  0); };
    static Pos offset_ul() { return Pos::offset_u() + Pos::offset_l(); };
    static Pos offset_ur() { return Pos::offset_u() + Pos::offset_r(); };
    static Pos offset_dl() { return Pos::offset_d() + Pos::offset_l(); };
    static Pos offset_dr() { return Pos::offset_d() + Pos::offset_r(); };
public:
    int v_;
    int h_;
};

class Map {
public:
    using CellIndex_T = size_t;
private:
    enum Cell_State {
        Sea = 0, Ground = 1
    };
public:
    Map(const int& v_size, const int& h_size): map_(v_size, vector<Cell_State>(h_size, Sea)) {
        for (size_t v = 0; v < v_size; ++v) {
            for (size_t h = 0; h < h_size; ++h) {
                int tstate; cin >> tstate;
                if (tstate == 0) map_[v][h] = Sea;
                else             map_[v][h] = Ground;
            }
        }
    };
    inline size_t size_v() const { return map_.size(); };
    inline size_t size_h() const { return map_.front().size(); };
    inline bool is_ground(const Pos& p) const { return is_ground(p.v_, p.h_); }
    inline bool is_ground(const CellIndex_T& v, const CellIndex_T& h) const { return map_[v][h] == Ground; }
    inline bool is_sea(const Pos& p) const { return is_sea(p.v_, p.h_); }
    inline bool is_sea(const CellIndex_T& v, const CellIndex_T& h) const { return map_[v][h] == Sea; }
public:
    int island_count() const {
        vector<vector<bool>> visited(size_v(), vector<bool>(size_h(), false));
        int island_count = 0;

        for (CellIndex_T v = 0; v < size_v(); ++v) {
        for (CellIndex_T h = 0; h < size_h(); ++h) {

            if (is_sea(v, h)) {
                continue;
            }

            if (visited[v][h]) {
                continue;
            }

            // Not visited Ground
            queue<Pos> to_visit; to_visit.push(Pos(v, h));
            visited[to_visit.front().v_][to_visit.front().h_] = true;

            while(!to_visit.empty()) {
                const auto cvisit = to_visit.front(); to_visit.pop();
                const auto& cadjs = cvisit.get_adj_poss(Pos(0, 0), Pos(size_v(), size_h()));
                for (const auto& cadj: cadjs) {
                    if (visited[cadj.v_][cadj.h_]) {
                        continue;
                    }

                    if (is_sea(cadj)) {
                        continue;
                    }
                    else { // is_ground(cadj)
                        visited[cadj.v_][cadj.h_] = true;
                        to_visit.push(cadj);
                    }
                }
            }

            if (is_ground(v, h)) {
                island_count++;
            }
        }}

        return island_count;
    }

#ifdef PS_DEBUG
public:
    void print() const {
        cout << "> Printing Map: \n";
        for (int v = 0; v < size_v(); ++v) {
            for (int h = 0; h < size_h(); ++h) {
                char delimeter;
                switch(map_[v][h]) {
                    default:
                    case Ground: delimeter = 'O'; break;
                    case Sea:    delimeter = '~'; break;
                }
                cout << delimeter;
            }
            cout << "\n";
        }
    }
#endif //PS_DEBUG 
private:
    vector<vector<Cell_State>> map_;
};

#define TC_LOOP_START while (true) {
#define TC_LOOP_END }
#define TC_LOOP_BREAK(expr) if(expr) break

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    TC_LOOP_START

    int w; cin >> w; const int& h_size = w; // [1, 50]
    int h; cin >> h; const int& v_size = h; // [1, 50]

    TC_LOOP_BREAK(h_size == 0 && v_size == 0);

    Map map(v_size, h_size);
    #ifdef PS_DEBUG
    map.print();
    cout << "\n";
    #endif //PS_DEBUG 

    cout << map.island_count() << '\n';

    TC_LOOP_END


    return 0;
}