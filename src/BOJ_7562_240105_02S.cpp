// title: 백준 7562 나이트의 이동 S1
// date: 2023-24-01T17:54

#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;
struct Pos {
    Pos(): v(0), h(0) {};
    Pos(size_t v, size_t h): v(v), h(h) {};
    Pos(const Pos& other): v(other.v), h(other.h) {};
    bool operator==(const Pos& right) const {
        return v == right.v && h == right.h;
    }
    Pos operator+(const Pos& right) const {
        return Pos(v + right.v, h + right.h);
    }
    friend istream& operator>>(istream& in, Pos& ref) {
        in >> ref.v >> ref.h;
        return in;
    }

    #ifdef PS_DEBUG
    inline void Print() const {
        cout << "[" << v << "][" << h << "]";
    }
    #endif //PS_DEBUG 

    inline bool IsInBound(const size_t board_size) const{
        return IsInBound(Pos(0, 0), Pos(board_size, board_size));
    }
    inline bool IsInBound(const Pos& min_bound, const Pos& max_bound) const {
        bool is_in_v_bound = min_bound.v <= v && v < max_bound.v;
        bool is_in_h_bound = min_bound.h <= h && h < max_bound.h;
        return is_in_v_bound && is_in_h_bound;
    }

    int v, h;
};
class Knight {
public:
    Knight(const Pos& start_pos, const size_t& board_size): pos_(start_pos), board_size_(board_size) {}
private:
    inline static vector<Pos> GetOffsets() {
        return vector<Pos> {
            Pos(+2, -1), Pos(+2, +1),
            Pos(-2, -1), Pos(-2, +1),
            Pos(+1, -2), Pos(+1, +2),
            Pos(-1, +2), Pos(-1, -2)
        };
    }
    vector<Pos> GetAdjacentPoses(const Pos& cvisit) const {
        vector<Pos> ret;
        for (const auto& offset: GetOffsets()) {
            const auto candid_pos = offset + cvisit;
            if (candid_pos.IsInBound(board_size_))
                ret.push_back(candid_pos);
        }
        return ret;
    }
public:
    size_t GetShortestDistance(const Pos& end_pos) {

        if (pos_ == end_pos)
            return 0;

        vector<vector<bool>> visited(board_size_, vector<bool>(board_size_, false));
        vector<vector<int>> distance(board_size_, vector<int>(board_size_, numeric_limits<int>::max()));
        queue<Pos> to_visit;

        to_visit.push(pos_); const auto& spos = to_visit.front();
        visited[spos.v][spos.h] = true;
        distance[spos.v][spos.h] = 0;

        while(!to_visit.empty()) {
            const auto cvisit = to_visit.front(); to_visit.pop();

            #ifdef PS_DEBUG
            for (size_t v = 0; v < board_size_; ++v) {
                for (size_t h = 0; h < board_size_; ++h) {
                    if (distance[v][h] == numeric_limits<int>::max())
                        cout << "X";
                    else cout << distance[v][h];
                }
                cout << "\n";
            }
            cout << "\n";
            #endif //PS_DEBUG 

            for (const auto& adj_pos: GetAdjacentPoses(cvisit)) {
                if (visited[adj_pos.v][adj_pos.h])
                    continue;

                visited[adj_pos.v][adj_pos.h] = true;
                distance[adj_pos.v][adj_pos.h] = distance[cvisit.v][cvisit.h] + 1;

                if (adj_pos == end_pos)
                    return distance[adj_pos.v][adj_pos.h];
                
                to_visit.push(adj_pos);
            }
        }

        return numeric_limits<int>::min(); // Error
    }
private:
    Pos pos_;
    size_t board_size_;
};


auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int tc_size; cin >> tc_size;
    for (size_t tc = 0; tc < tc_size; ++tc) {
        int l; cin >> l; const int& board_size = l; // [4, 300]
        Pos start_pos; cin >> start_pos;
        Pos end_pos; cin >> end_pos;

        Knight knight(start_pos, board_size);
        cout << knight.GetShortestDistance(end_pos) << '\n';
    }

    return 0;
}