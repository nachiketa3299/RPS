// 백준 2667 단지번호 붙이기 S1
// 2023-12-20 23:15 00:17 50

#define PS_DEBUG
#undef PS_DEBUG
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <array>

using namespace std;

struct Pos
{
    Pos(int x, int y): x_(x), y_(y) {};
    int x_{0};
    int y_{0};

    Pos operator+(const Pos& r) { return { x_ + r.x_, y_ + r.y_ }; };
    vector<Pos> GetAdjacentPoss(size_t max_boundary)
    {
        static array<Pos, 4> offsets = {{ Pos(0, +1), Pos(0, -1), Pos(+1, 0), Pos(-1, 0) }};
        vector<Pos> ret;
        for (const auto& offset: offsets)
        {
            Pos t = *this + offset;
            if (!(0 <= t.x_ && t.x_ < max_boundary)) continue;
            if (!(0 <= t.y_ && t.y_ < max_boundary)) continue;
            ret.push_back(t);
        }
        return ret;
    }
};

class Map
{
public:
    Map(const int N): map_(N, vector<bool>(N, 0))
    {
        cin.ignore();
        for (size_t i = 0; i < N; ++i)
        {
            string line; getline(cin, line);
            transform(line.begin(), line.end(), map_[i].begin(), [](auto& c){ return c == '1'; });
        }
        return;
    }
public:
    vector<int> GetSwarmInfo() const
    {
        vector<vector<bool>> total_visited(map_size(), vector<bool>(map_size(), false));
        vector<int> ret;
        const auto& has_house = map_;
        for (size_t i = 0; i < map_size(); ++i)
        {
            for (size_t j = 0; j < map_size(); ++j)
            {
                if (total_visited[i][j]) 
                    continue;

                if (has_house[i][j])
                {
                    #ifdef PS_DEBUG
                    cout << "Start with (" << i << "," << j << ")\n";
                    #endif //PS_DEBUg
                    int house_cnt = 0;
                    queue<Pos> to_visit; 

                    to_visit.push(Pos(i, j));
                    static vector<vector<bool>> visited(map_size(), vector<bool>(map_size(), false));

                    visited[i][j] = total_visited[i][j] = true;

                    while(!to_visit.empty())
                    {
                        house_cnt++;
                        auto cvisit = to_visit.front(); to_visit.pop();

                        #ifdef PS_DEBUG
                        cout << "- visited (" << cvisit.x_ << "," << cvisit.y_ << ") count: "<< house_cnt << "\n";
                        #endif //PS_DEBUg

                        const auto adjs = cvisit.GetAdjacentPoss(map_size());
                        for (const auto& adj: adjs)
                        {
                            if (!has_house[adj.x_][adj.y_])
                                continue;
                            if(visited[adj.x_][adj.y_])
                                continue;

                            visited[adj.x_][adj.y_] = total_visited[adj.x_][adj.y_] = true;

                            to_visit.push(adj);
                        }
                    }

                    ret.push_back(house_cnt);
                }
            }
        }
        sort(ret.begin(), ret.end());
        return ret;
    }
    inline size_t map_size() const { return map_.size(); };
#ifdef PS_DEBUG
public:
    void Print() const 
{
    for (const auto& l: map_)
    {
        for (const auto& e: l)
        {
            if (e) cout << "1";
            else cout << "0";
        }
        cout << '\n';
    }
    cout << '\n';
}
#endif //PS_DEBUG
private:
    vector<vector<bool>> map_;
};

int main()
{
    int N; cin >> N; 
    Map map(N);
    const auto swarm_info = map.GetSwarmInfo();

    cout << swarm_info.size() << '\n';
    for (const auto& e: swarm_info) 
        cout << e << '\n';
    return 0;
}

