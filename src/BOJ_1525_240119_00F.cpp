// title: 백준 1525 퍼즐 G2
// date: 11:10 - 11:48 (첫 제출, 틀렸습니다)
// Failed. 이것도 상태를 저장하는 Advanced BFS임

#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>

using namespace std;

using Pos_t = int;
constexpr Pos_t kInvalidPos = -1;

struct Pos2_t {
    Pos_t v = kInvalidPos;
    Pos_t h = kInvalidPos;
    Pos2_t operator+(const Pos2_t& other) const {
        return Pos2_t { v + other.v, h + other.h };
    }
    static vector<Pos2_t> Get_RLUD_Offsets() {
        return vector<Pos2_t>{ Pos2_t{ -1, 0 }, Pos2_t{ +1, 0 },Pos2_t{ 0, -1 },Pos2_t{ 0, +1 } };
    }
};

using Weight_t = int;
constexpr Weight_t kInfiniteWeight = numeric_limits<Weight_t>::max();
constexpr Weight_t kZeroWeight = 0;
constexpr int kPathFindError = -1;

class Board {
    using CardNum_t = size_t;
    static constexpr int kVH_Size = 3;
    static constexpr CardNum_t kBlankCard = 0;
public:
    Board() 
        : board_(kVH_Size, vector<CardNum_t>(kVH_Size, kBlankCard))
    {
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                auto& c_cell = board_[v][h];
                cin >> c_cell;
                if (c_cell == kBlankCard)
                    s_pos_ = Pos2_t { (int)v, (int)h };
            }
        }
    }
    vector<Pos2_t> MakeAdjacentPoses(const Pos2_t& pos) const {
        vector<Pos2_t> ret;
        for (const auto& offset: Pos2_t::Get_RLUD_Offsets()) {
            const auto& c_pos = pos + offset;
            if (!(0 <= c_pos.v && c_pos.v < size_v()))
                continue;
            if (!(0 <= c_pos.h && c_pos.h < size_h()))
                continue;
            ret.push_back(c_pos);
        }
        return ret;
    }
    inline CardNum_t GetProperCardNumAt(const Pos2_t& pos) {
        return kVH_Size * pos.v + pos.h + 1;
    }
    inline CardNum_t& GetCardNumRefAt(const Pos2_t& pos) {
        return board_[pos.v][pos.h];
    }
    inline void SwapCardNum(const Pos2_t& left, const Pos2_t& right) {
        swap(board_[left.v][left.h], board_[right.v][right.h]);
    }
    Weight_t BFS_ShortestPath() {
        queue<Pos2_t> to_visit;
        vector<vector<bool>> visited(size_v(), vector<bool>(size_h(), false));
        vector<vector<Weight_t>> distance(size_v(), vector<Weight_t>(size_h(), kInfiniteWeight));

        to_visit.push(s_pos_);
        visited[s_pos_.v][s_pos_.h] = true;
        distance[s_pos_.v][s_pos_.h] = kZeroWeight;

        while (!to_visit.empty()) {
            const auto cv_pos = to_visit.front();
            to_visit.pop();

            for (const auto& adj_pos: MakeAdjacentPoses(cv_pos)) {
                if (!(GetProperCardNumAt(cv_pos) == GetCardNumRefAt(adj_pos)))
                    continue;
                if (visited[adj_pos.v][adj_pos.h])
                    continue;
                visited[adj_pos.v][adj_pos.h] = true;
                distance[adj_pos.v][adj_pos.h] = distance[cv_pos.v][cv_pos.h] + 1;
                SwapCardNum(cv_pos, adj_pos);

                to_visit.push(adj_pos);
            }
        }
        return distance[size_v() - 1][size_h() - 1];
    }
    

    inline size_t size_v() const {
        return kVH_Size;
    }
    inline size_t size_h() const {
        return kVH_Size;
    }

private:
    vector<vector<CardNum_t>> board_;
    Pos2_t s_pos_;
};

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }


    Board board;
    const auto dist = board.BFS_ShortestPath();
    switch (dist) {
        case kInfiniteWeight:
            cout << kPathFindError;
            break;
        default:
            cout << dist;
            break;
    }

    return 0;
}