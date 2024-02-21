/*
- u_title: 백준 2234 성곽 G3
  time: 16:03
  note:
*/

#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <vector>

#define PS_DEBUG
// #undef PS_DEBUG

#define PS_IO_OPT                                                                      \
    std::ios_base::sync_with_stdio(false);                                             \
    std::cin.tie(nullptr);                                                             \
    std::cout.tie(nullptr);

using namespace std;

struct Pos2_t
{
public:
    static constexpr int INV_POS = -1;

public:
    static constexpr Pos2_t EastPos2()
    {
        return Pos2_t{0, +1};
    }
    static constexpr Pos2_t WestPos2()
    {
        return Pos2_t{0, -1};
    }
    static constexpr Pos2_t NorthPos2()
    {
        return Pos2_t{-1, 0};
    }
    static constexpr Pos2_t SouthPos2()
    {
        return Pos2_t{+1, 0};
    }

public:
    static vector<Pos2_t> GetPos2Offsets()
    {
        return vector<Pos2_t>{
            Pos2_t{-1, 0 },
            Pos2_t{+1, 0 },
            Pos2_t{0,  -1},
            Pos2_t{0,  +1}
        };
    }
    Pos2_t operator+(const Pos2_t& other) const
    {
        return Pos2_t{v + other.v, h + other.h};
    }
    bool operator<(const Pos2_t& other) const
    {
        return v < other.v;
    }

public:
    int v{INV_POS};
    int h{INV_POS};
};

class Castle
{
public:
    using Wall_t = bitset<4>;

public:
    static constexpr Wall_t WEST  = Wall_t(1);
    static constexpr Wall_t NORTH = Wall_t(2);
    static constexpr Wall_t EAST  = Wall_t(4);
    static constexpr Wall_t SOUTH = Wall_t(8);

public:
    inline static const map<Pos2_t, Wall_t> otob{
        {Pos2_t::WestPos2(),  WEST },
        {Pos2_t::EastPos2(),  EAST },
        {Pos2_t::NorthPos2(), NORTH},
        {Pos2_t::SouthPos2(), SOUTH},
    };

public:
    Castle(int v_size, int h_size)
        : m_walls(v_size, vector<Wall_t>(h_size))
    {
        for (int v = 0; v < v_size; ++v)
        {
            for (int h = 0; h < h_size; ++h)
            {
                int i;
                cin >> i;
                m_walls[v][h] = Wall_t(i);
            }
        }
    }
    inline size_t size_v() const
    {
        return m_walls.size();
    }
    inline size_t size_h() const
    {
        return m_walls.front().size();
    }

public:
    vector<Pos2_t> GetAdjPos2s(const Pos2_t& pivot) const
    {
        vector<Pos2_t> ret;
        for (const auto& offsets: Pos2_t::GetPos2Offsets())
        {
            const auto c_pos = pivot + offsets;

            if (0 <= c_pos.v && c_pos.v < size_v())
                continue;

            if (0 <= c_pos.h && c_pos.h < size_h())
                continue;

            ret.push_back(c_pos);
        }
        return ret;
    }
    inline bool HasWall(const Pos2_t& offset, const Pos2_t& pivot) const
    {
        auto bitval  = m_walls[pivot.v][pivot.h];
        bitval      &= otob.at(offset);
        return bitval.any();
    }
    vector<Pos2_t> GetNonWallAdjPos2s(const Pos2_t& pivot) const
    {
        vector<Pos2_t> ret;
        for (const auto& offset: Pos2_t::GetPos2Offsets())
        {
            const auto c_pos = offset + pivot;

            if (!(0 <= c_pos.v && c_pos.v < size_v()))
                continue;

            if (!(0 <= c_pos.h && c_pos.h < size_h()))
                continue;

            if (HasWall(offset, pivot))
                continue;

            ret.push_back(c_pos);
        }
        return ret;
    }
    vector<Pos2_t> GetWallAdjPos2s(const Pos2_t& pivot) const
    {
        vector<Pos2_t> ret;
        for (const auto& offset: Pos2_t::GetPos2Offsets())
        {
            const auto c_pos = offset + pivot;

            if (!(0 <= c_pos.v && c_pos.v < size_v()))
                continue;

            if (!(0 <= c_pos.h && c_pos.h < size_h()))
                continue;

            if (!HasWall(offset, pivot))
                continue;

            ret.push_back(c_pos);
        }
        return ret;
    }
    void BFS() const
    {
        for (int v = 0; v < size_v(); ++v)
        {
            for (int h = 0; h < size_h(); ++h)
            {
                const auto c_pos      = Pos2_t{v, h};
                const auto w_adj_pos  = GetWallAdjPos2s(c_pos);
                const auto nw_adj_pos = GetNonWallAdjPos2s(c_pos);
            }
        }
    }

private:
    vector<vector<Wall_t>> m_walls;
};

auto main() -> int
{
    PS_IO_OPT
    int N, M;
    cin >> N >> M;
    const auto& v_size = M;
    const auto& h_size = N;

    Castle      c(v_size, h_size);
    c.BFS();

    return EXIT_SUCCESS;
}