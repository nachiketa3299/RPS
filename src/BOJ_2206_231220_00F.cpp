// 백준 2206 벽 부수고 이동하기
// 2023-12-20 T 17:43
// 2초, 192MB

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;
#define C_WALL '1'
#define C_PATH '0'
#define START_N 1-1
#define START_M 1-1

struct Pos
{
    int n_{0}, m_{0};
    static Pos offset_R() { return { 0, +1}; };
    static Pos offset_L() { return { 0, -1}; };
    static Pos offset_U() { return {-1,  0}; };
    static Pos offset_D() { return {+1,  0}; };
    Pos operator+(const Pos& right) const { return { n_ + right.n_, m_ + right.m_ };};
    Pos& operator+=(const Pos& right) { n_ += right.n_; m_ += right.m_; return *this; }
};

class Map
{
public:
    Map(const vector<string>& tmap): has_wall_(tmap.size(), vector<bool>(tmap.front().size(), false))
    {
        for (size_t n = 0; n < has_wall_.size(); ++n)
        {
            for (size_t m = 0; m < has_wall_.front().size(); ++m)
            {
                switch(tmap[n][m])
                {
                    case C_WALL: has_wall_[n][m] = true; break;
                    case C_PATH: has_wall_[n][m] = false; break;
                }
            }
        }
    }
public:
    int CalBreakWallCount() 
    {
        vector<vector<vector<bool>>> visited(map_n(), vector<vector<bool>>(map_m(), vector<bool>(2, false)));
        
    };
    inline size_t map_n() const { return has_wall_.size(); };
    inline size_t map_m() const { return has_wall_.front().size(); };
private:
    vector<vector<bool>> has_wall_;
};

auto main() -> int
{
    int N; cin >> N; // [1, 1e3]
    int M; cin >> M; // [1, 1e3]
    cin.ignore();
    vector<string> tmap(N);
    for (auto& line: tmap) 
        getline(cin, line);

    Map map(tmap);
    cout << map.CalBreakWallCount() << '\n';

    return 0;
}