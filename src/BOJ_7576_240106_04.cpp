// title: 백준 7576 토마토 G5
// date: 2023-01-05T19:10 20:00 stop 2024-01-05T20:55 21:09 50 + 14 = 64
#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

struct Pos {
    Pos(const size_t& iv=0, const size_t ih=0): v(iv), h(ih) {};
    Pos(const Pos& other): v(other.v), h(other.h) {};
    Pos operator+(const Pos& other) const {
        return Pos(v + other.v, h + other.h);
    }
    static vector<Pos> GetOffsets() {
        return vector<Pos> {
            Pos(+1, 0), Pos(-1, 0), Pos(0, +1), Pos(0, -1)
        };
    }
    inline bool IsInBound(const size_t& max_size_v, const size_t& max_size_h) const {
        return IsInBound(Pos(0, 0), Pos(max_size_v, max_size_h));
    }
    inline bool IsInBound(const Pos& min_vh, const Pos& max_vh) const {
        const bool is_in_v_bound = min_vh.v <= v && v < max_vh.v;
        const bool is_in_h_bound = min_vh.h <= h && h < max_vh.h;
        return is_in_v_bound && is_in_h_bound;
    }
    int v, h;
};

namespace tomato {

constexpr int kCantRipeAll = -1;
constexpr int kAlreadyAllRiped = 0;

enum State {
    Empty = -1, Unriped = 0, Riped = 1
};
istream& operator>>(istream& in, State& tstate) {
    int state_int; in >> state_int;
    tstate = (State)state_int;
    return in;
}


class Box {
public:
    Box(const size_t& box_size_v, const size_t& box_size_h): box_(box_size_v, vector<State>(box_size_h, Empty)) {
        for (size_t v = 0; v < size_v(); ++v)
            for (size_t h = 0; h < size_h(); ++h)
                cin >> box_[v][h];
    }
    inline size_t size_v() const { return box_.size(); };
    inline size_t size_h() const { return box_.front().size(); };
private:
    vector<Pos> GetAdjacentPoses(const Pos& pivot_pos) const {
        vector<Pos> ret;
        for (const auto& offset: Pos::GetOffsets()) {
            const auto candid_pos = offset + pivot_pos;
            if (candid_pos.IsInBound(size_v(), size_h()))
                ret.push_back(candid_pos);
        }
        return ret;
    }
public:
    int GetDaysToAllRipe() {
        vector<vector<bool>> visited(size_v(), vector<bool>(size_h(), false));
        vector<vector<int>> distance(size_v(), vector<int>(size_h(), numeric_limits<int>::min()));
        queue<Pos> to_visit;

        // 처음에 Riped 인 녀석들을 큐에 넣는다.
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                if (box_[v][h] == Riped) {
                    visited[v][h] = true;
                    distance[v][h] = 0;
                    to_visit.push(Pos(v, h));
                }
            }
        }

        while(!to_visit.empty()) {
            const auto cvisit = to_visit.front(); to_visit.pop();
            // 현재 방문중인 셀의 인접한 셀들을 가져온다.
            #ifdef PS_DEBUG
            cout << "> Visiting: [" << cvisit.v << "][" << cvisit.h << "]\n";
            #endif //PS_DEBUG 
            for (const auto& adj_pos: GetAdjacentPoses(cvisit)) {
                if (visited[adj_pos.v][adj_pos.h]) {
                    #ifdef PS_DEBUG
                    PrintDays(distance);
                    #endif //PS_DEBUG 
                    continue;
                }

                auto& cstate = box_[adj_pos.v][adj_pos.h];

                if (cstate == Empty || cstate == Riped) {
                    #ifdef PS_DEBUG
                    PrintDays(distance);
                    #endif //PS_DEBUG 
                    continue;
                }

                else if (cstate == Unriped) {
                    cstate = Riped;
                    distance[adj_pos.v][adj_pos.h] = distance[cvisit.v][cvisit.h] + 1;
                    visited[adj_pos.v][adj_pos.h] = true;
                    to_visit.push(adj_pos);
                    #ifdef PS_DEBUG
                    PrintDays(distance);
                    #endif //PS_DEBUG 
                }
            }
        }

        auto max_days = numeric_limits<int>::min();
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                if (box_[v][h] == Unriped)
                    return kCantRipeAll;
                if (box_[v][h] == Riped) {
                    max_days = max(distance[v][h], max_days);
                }
            }
        }
        return max_days;

    }
#ifdef PS_DEBUG
public:
    void PrintDays(const vector<vector<int>>& distance) const {
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                if (distance[v][h] < 0) cout << "X";
                else cout << distance[v][h];
            }
            cout << '\n';
        }
        cout << '\n';
    }
    void Print() const {
        char del;
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                switch(box_[v][h]) {
                    default: 
                    case Empty: del = 'X'; break;
                    case Unriped: del = 'U'; break;
                    case Riped: del = 'R'; break;
                }
                cout << del;
            }
            cout << '\n';
        }
        cout << '\n';
    }
#endif //PS_DEBUG 
private:
    vector<vector<State>> box_;
};

} // namespace tomato

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int M, N; cin >> M >> N;
    const int& box_size_h = M; // [2, 1000]
    const int& box_size_v = N; // [2, 1000]

    tomato::Box box(box_size_v, box_size_h);

    #ifdef PS_DEBUG
    cout << "> Input Test:\n";
    box.Print();
    #endif //PS_DEBUG 

    cout << box.GetDaysToAllRipe();

    return 0;
}