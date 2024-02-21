// title: 백준 11650 좌표 정렬하기 S5
// date: 19:15 19:24 (9)
#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Pos2 {
public:
    Pos2(): v(0), h(0) {}
    Pos2(const int& v, const int& h): v(v), h(h) {}
    Pos2(const Pos2& pos): v(pos.v), h(pos.h) {}
public:
    inline bool IsInBound(const Pos2& min_vh, const Pos2& max_vh) const {
        const bool is_in_v_bound = min_vh.v <= v && v < max_vh.v;
        const bool is_in_h_bound = min_vh.h <= h && h < max_vh.h;
        return is_in_v_bound && is_in_h_bound;
    }
public:
    friend istream& operator>>(istream& is, Pos2& pos) {
        is >> pos.v >> pos.h;
        return is;
    }
    friend ostream& operator<<(ostream& os, const Pos2& pos) {
        os << pos.v << " " << pos.h << '\n';
        return os;
    }
    Pos2 operator+(const Pos2& other) const {
        return Pos2(v + other.v, h + other.h);
    }
    bool operator==(const Pos2& other) const {
        return v == other.v && h == other.h;
    }
public:
    int v, h;
};

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int N; cin >> N;
    vector<Pos2> poss(N);
    for_each(poss.begin(), poss.end(), [](auto& pos) { cin >> pos; });
    auto pred = [](const Pos2& pos_l, const Pos2& pos_r) {
        if (pos_l.v != pos_r.v) 
            return pos_l.v < pos_r.v;
        else 
            return pos_l.h < pos_r.h;
    };
    stable_sort(poss.begin(), poss.end(), pred);
    for_each(poss.begin(), poss.end(), [](const auto& pos) { cout << pos; });
    
    return 0;
}