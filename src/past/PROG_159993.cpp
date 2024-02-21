
#include "PROG.h"


/// @date 2023-11-09T17:30 18:24 (54)
/// 프로그래머스 미로 탈출 L2
/*!
* 1x1 칸으로 이루어진 직사각형 격자 형태의 미로에서 탈출하려고 한다.
* 각 칸은 통로 또는 벽으로 구성되어 있다. 
* 벽으로 된 칸은 지나갈 수 없다.
* 통로로 된 칸으로만 이동할 수 있다.
* 통로들 중 한 칸에는 미로를 빠져나가는 문이 있다.
* 그런데 이 문은 레버를 당겨야 열리며, 레버 또한 통로들 중 한 칸에 있다.
* 따라서 출발 지점 -> 레버가 있는 칸 -> 출구 칸 으로 이동해야한다.
* 레버를 당기지 않았더라도 출구가 있는 칸을 경유할 수는 있다.
* 미로에서 한 칸을 이동하는데 걸리는 시간은 1초이다.
* 
* 미로의 구조가 주어질 때, 미로를 빠져나가는 데에 걸리는 최소의 시간을 구한다.
* 탈출할 수 없으면 -1을 리턴한다.
* 미로의 구조는 문자열 벡터 `maps` 이다. 길이는 [5, 100]
* `S` 시작 지점 `E` 출구 `L` 레버 `O` 통로 `X` 벽
* `S`, `E`, `L` 은 항상 다른 곳에 존재하며 하나만 존재한다.
* 모든 `S`, `E`, `L`은 여러 번 지나갈 수 있다.
*/

#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

enum class CellType { Start, Exit, Lever, Path, Wall, None };
const map<char, CellType> CTOT =
{
    {'S', CellType::Start},
    {'E', CellType::Exit},
    {'L', CellType::Lever},
    {'O', CellType::Path},
    {'X', CellType::Wall},
};

struct Cell
{
    Cell() {};
    Cell(const char& ctype_char): type(::CTOT.at(ctype_char)) { };
    bool is_wall() const { return type == CellType::Wall; }
    CellType type = CellType::None;
};

typedef size_t IndexType;
typedef int DistanceType;
typedef DistanceType TimeType;

class Maze
{
public:
    Maze(const vector<string>& maps, size_t i_size, size_t j_size): 
        cells(i_size * j_size), 
        i_size(i_size), 
        j_size(j_size),
        adj_list(cells.size())
    {
        // Make Cells
        for (size_t i = 0; i < i_size; ++i)
            for (size_t j = 0; j < j_size; ++j)
                cells[toidx(i, j)].type = ::CTOT.at(maps[i][j]);

        // Tie Cells
        for (size_t i = 0; i < i_size; ++i)
        {
            for (size_t j = 0; j < j_size; ++j)
            {
                if (cells[toidx(i, j)].is_wall()) 
                    continue;
                switch (cells[toidx(i, j)].type)
                {
                case CellType::Start: idx_start = toidx(i, j); break;
                case CellType::Lever: idx_lever = toidx(i, j); break;
                case CellType::Exit: idx_exit = toidx(i, j); break;
                default: break;
                }

                const IndexType up = i - 1;
                const IndexType down = i + 1;
                const IndexType left = j - 1;
                const IndexType right = j + 1;

                if (i > 0 && !cells[toidx(up, j)].is_wall())
                    adj_list[toidx(i, j)].push_back(toidx(up, j));
                if (i < i_size - 1 && !cells[toidx(down, j)].is_wall())
                    adj_list[toidx(i, j)].push_back(toidx(down, j));
                if (j > 0 && !cells[toidx(i, left)].is_wall())
                    adj_list[toidx(i, j)].push_back(toidx(i, left));
                if (j < j_size - 1 && !cells[toidx(i, right)].is_wall())
                    adj_list[toidx(i, j)].push_back(toidx(i, right));
            }
        }
    }
    inline IndexType toidx(IndexType i, IndexType j) { return j + i * j_size; }

    TimeType get_minimum_exit_time() const
    {
        int stol = bfs_distance(idx_start, idx_lever);

        if (stol == -1) return -1;

        int ltoe = bfs_distance(idx_lever, idx_exit);

        if (ltoe == -1) return -1;

        return stol + ltoe;
    }

    DistanceType bfs_distance(IndexType bfs_start, IndexType bfs_end) const
    {
        // Initial Queue
        queue<IndexType> to_visit;
        to_visit.push(bfs_start);

        // Initial Visited
        vector<bool> visited(cells.size(), false); 
        visited[to_visit.front()] = true;

        // Initial Distance
        vector<DistanceType> distance(cells.size(), -1); 
        distance[bfs_start] = 0;

        return bfs_distance_recur(to_visit, visited, distance, bfs_end);
    }
    DistanceType bfs_distance_recur(queue<IndexType>& to_visit, vector<bool> visited, vector<DistanceType>& distance, IndexType& bfs_recur_end) const
    {
        auto ccell_idx = to_visit.front(); 
        to_visit.pop();

        if (ccell_idx == bfs_recur_end) 
            return distance[ccell_idx];

        for (auto& adj_ccell_idx : adj_list[ccell_idx])
        {
            if (visited[adj_ccell_idx]) continue;
            visited[adj_ccell_idx] = true;
            to_visit.push(adj_ccell_idx);
            distance[adj_ccell_idx] = distance[ccell_idx] + 1;
        } 

        if (to_visit.empty()) return -1;

        return bfs_distance_recur(to_visit, visited, distance, bfs_recur_end);
    }

private:
    vector<Cell> cells;
    vector<vector<IndexType>> adj_list;

    IndexType idx_start;
    IndexType idx_lever;
    IndexType idx_exit;

    size_t i_size;
    size_t j_size;
};

int solution(vector<string> maps)
{
    const size_t i_size = maps.size();
    const size_t j_size = maps.front().size();

    Maze mz(maps, i_size, j_size);
    return mz.get_minimum_exit_time();
}

int main()
{
    Solver<vector<string>, int> s =
    {
        {
            { {"SOOOL","XXXXO","OOOOO","OXXXX","OOOOE"}, 16},
            { {"LOOXS","OOOOX","OOOOO","OOOOO","EOOOO"}, -1},
            { {"ESL"} , 3},
            { {"E", "S", "L"} , 3}
        }
    }; s();
    return 0;
}




