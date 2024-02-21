/// @file BOJ_23288_231130.cpp

#define DEBUG
#undef DEBUG

#ifdef DEBUG
#include <string>
#endif

/*!
* 크기가 N x M인 지도 (우측이 동쪽, 위쪽이 북쪽)
* 지도의 좌표는 (r, c), r은 북쪽으로부터 떨어진 칸의 갯수, c는 서쪽으로부터 떨어진 칸의 갯수.
* 가장 왼쪽에 있는 칸의 좌표는 (1, 1)
* 가장 오른쪽 아래에 있는 칸의 좌표는 (N, M)
* 지도위에 지도 한 칸과 한 면의 크기가 같은 주사위 하나, 각 면에 1~6 사이 정수가 하나씩 적힘. 전개도는 아래와 같다.
*  2
* 413
*  5
*  6
* 주사위는 지도 위에 윗면이 1이고, 동쪽을 바라보면 방향이 3인 상태로 놓여져 있고 놓여져 있는 곳의 좌표는 (1,1)
* 지도의 각 칸에 정수가 존재
* 처음 주사위 이동 방향은 동쪽
* 주사위 이동 한 번은 다음과 같이 이루어짐
* - 주사위는 이동 방향으로 한 칸 굴러간다. 이동 방향에 칸이 없으면, 반대로 하고 한 칸 굴러간다.
* - 주사위가 도착한 칸 (x, y)에 대한 점수를 획득한다.
* - 주사위의 아랫면에 있는 정수 A와 주사위가 있는 칸 (x, y)에 있는 정수 B를 비교해 이동 방향을 결정한다.
*   - A > B 면 이동 방향을 90도 시계 방향으로 회전시킨다.
*   - A < B 면 이동 방향을 90도 반시계 방향으로 회전시킨다.
*   - A = B 면 이동 방향에 변화는 없다.
* 칸 (x, y)에 대한 점수는 다음과 같이 구한다.
* (x, y)에 있는 정수를 B라고 할 때, (x, y)에서 동서남북 방향으로 연속해 이동할 수 있는 칸의 수 C를 모두 구한다.
* 이 때 이동할 수 있는 칸에는 모두 정수 B가 있어야 한다. 여기서 점수는 B와 C를 곱한 값이다.
* 보드의 크기와 각 칸에 있는 정수, 주사위의 이동 횟수 K가 주어질 때, 각 이동에서 획득하는 점수의 합을 구한다.
*/

#include <iostream>
#include <vector>
#include <array>
#include <queue>

using namespace std;

using SizeType = int;
using CountType = int;
using ScoreType = int;

struct Position
{
public:
    Position(SizeType v = 0, SizeType h = 0):v(v), h(h) {}
public:
    void MoveToNorth() { this->v += -1; return; }
    void MoveToSouth() { this->v += +1; return; }
    void MoveToEast() { this->h += +1; return; }
    void MoveToWest() { this->h += -1; return; }
public:
    Position operator+(const Position& right) const { return Position(this->v + right.v, this->h + right.h); };
public:
    SizeType v = 0;
    SizeType h = 0;
};

enum EDiceDirection { East = 0, North, West, South, DirectionMax };
enum EDiceSides { Top = 0, Bottom, Right, Left, Up, Down, SideMax };

class Dice
{
public:
    Dice()
    {
        /*!
        * 주사위는 아래처럼 정의된다.
        *          [  UP  ]
        * [ LEFT ] [ TOP  ] [ RIGHT]
        *          [ DOWN ]
        *          [BOTTOM]
        */
        this->sides[Top]    = 1;
        this->sides[Bottom] = 6;
        this->sides[Left]   = 4;
        this->sides[Right]  = 3;
        this->sides[Up]     = 2;
        this->sides[Down]   = 5;
        return;
    }
    Dice(const Dice& dice): 
        sides(dice.sides),
        position(dice.position),
        direction(dice.direction)
    {}
public:
    const Position& GetPosition() const { return this->position; };
    const ScoreType& GetBottomScore() const { return this->sides[Bottom]; };
private:
    const ScoreType GetCachedBottom() const { return this->bottom_cache; };
    void CacheBottom() { this->bottom_cache = this->GetBottomScore(); return; };
public:
    void InvertDirection()
    {
        switch (this->direction)
        {
        case East: 
            this->direction = West; 
            break;
        case North: 
            this->direction = South; 
            break;
        case West: 
            this->direction = East; 
            break;
        case South: 
            this->direction = North; 
            break;
        default:
        case DirectionMax:
            return;
        }
        return;
    }
    /*!
     * @brief 주사위의 방향을 시계방향(Clockwise)으로 90도 돌린다.
    */
    void RotateDirectionC90()
    {
        this->direction = (this->direction - 1 < 0 ? South : static_cast<EDiceDirection>(this->direction - 1));
        return;
    }
    /*!
     * @brief 주사위의 방향을 반시계방향(Counter-Clockwise)으로 돌린다.
    */
    void RotateDirectionCC90()
    {
        this->direction = (this->direction + 1 == DirectionMax ? East : static_cast<EDiceDirection>(this->direction + 1));
        return;
    }
    /*!
     * @brief 주사위를 설정된 방향으로 굴린다.
    */
    void Roll()
    {
        this->CacheBottom();
        switch (this->direction)
        {
        case East: 
            this->RollToEast(); 
            break;
        case North: 
            this->RollToNorth(); 
            break;
        case West: 
            this->RollToWest(); 
            break;
        case South: 
            this->RollToSouth(); 
            break;

        default:
        case DirectionMax:
            return;
        }
        return;
    }
#ifdef DEBUG
public:
    void PrintDice() const
    {
        cout << "** Dice State:\n";
        cout << "  " << this->sides[Up] << '\n';
        cout << this->sides[Left] << " " << this->sides[Top] << " " << this->sides[Right] << '\n';
        cout << "  " << this->sides[Down] << '\n';
        cout << "  " << this->sides[Bottom] << '\n';
        return;
    }
    string GetDirectionString() const
    {
        switch (this->direction)
        {
        case East: 
            return "East";
        case North: 
            return "North";
        case South: 
            return "South";
        case West: 
            return "West";
        default: 
            break;
        }
        return "ERROR";
    }
#endif

private:
    void RollToNorth() // ↑
    {
        this->position.MoveToNorth();

        this->sides[Bottom]     = this->sides[Up];
        this->sides[Up]         = this->sides[Top];
        this->sides[Top]        = this->sides[Down];
        this->sides[Down]       = this->GetCachedBottom();
        return;
    }
    void RollToSouth() // ↓
    {
        this->position.MoveToSouth();

        this->sides[Bottom]     = this->sides[Down];
        this->sides[Down]       = this->sides[Top];
        this->sides[Top]         = this->sides[Up];
        this->sides[Up]        = this->GetCachedBottom();
        return;
    }
    void RollToWest() // ←
    {
        this->position.MoveToWest();

        this->sides[Bottom]     = this->sides[Left];
        this->sides[Left]       = this->sides[Top];
        this->sides[Top]         = this->sides[Right];
        this->sides[Right]      = this->GetCachedBottom();
        return;
    }
    void RollToEast() // →
    {
        this->position.MoveToEast();

        this->sides[Bottom]     = this->sides[Right];
        this->sides[Right]      = this->sides[Top];
        this->sides[Top]         = this->sides[Left];
        this->sides[Left]       = this->GetCachedBottom();
        return;
    }
private:
    Position position;
    EDiceDirection direction = East;
    array<ScoreType, SideMax> sides;
private:
    ScoreType bottom_cache =0;
};

class Map
{
public:
    Map(vector<vector<ScoreType>>& map_scores):
        map_scores(move(map_scores))
    { };
    /*!
     * @brief BFS 방식으로 인접했으면서 같은 숫자를 가진 타일을 탐색함
     * @param position 시작 타일의 위치
     * @return 시작 타일에서 동서남북으로 연속하여 인접했으면서 시작 타일과 점수가 같은 타일의 갯수 (시작 타일을 포함하므로 최소는 1)
    */
    CountType GetAdjacentSameScoreCounts(const Position& position)
    {
        const ScoreType& score_target = this->GetScoreByPosition(position);

        queue<Position> to_visit; to_visit.push(position);
        vector<vector<bool>> visited(this->GetVSize(), vector<bool>(this->GetHSize(), false));

        vector<Position> hit_targets;
        hit_targets.push_back(position);

        while (!to_visit.empty())
        {
            const Position& visiting = to_visit.front();
            visited[visiting.v][visiting.h] = true;
            vector<Position> adjacents;
            adjacents.push_back(visiting + Position(0, -1));
            adjacents.push_back(visiting + Position(0, +1));
            adjacents.push_back(visiting + Position(+1, 0));
            adjacents.push_back(visiting + Position(-1, 0));

            for (const auto& adjacent : adjacents)
            {

                if (!this->IsInBound(adjacent)) continue;
                if (!(this->GetScoreByPosition(adjacent) == score_target)) continue;
                if (visited[adjacent.v][adjacent.h]) continue;

                visited[adjacent.v][adjacent.h] = true;
                to_visit.push(adjacent);
                hit_targets.push_back(adjacent);
            }
            to_visit.pop();
        }

        return hit_targets.size();
    }
public:
    const ScoreType& GetScoreByPosition(const Position& pos) const { return this->map_scores[pos.v][pos.h]; };
public:
    bool IsInBound(const Position& pos) const { return this->IsInHBound(pos) && this->IsInVBound(pos); };
private:
    bool IsInVBound(const Position& pos) const { return pos.v < this->GetVSize() && pos.v >= 0; };
    bool IsInHBound(const Position& pos) const { return pos.h < this->GetHSize() && pos.h >= 0; }
public:
    SizeType GetVSize() const { return this->map_scores.size(); }
    SizeType GetHSize() const { return this->map_scores.front().size(); };
#ifdef DEBUG
    void PrintMapWithPosition(const Position& pos) const
    {
        for (SizeType v = 0; v < this->GetVSize(); ++v)
        {
            for (SizeType h = 0; h < this->GetHSize(); ++h)
            {
                string del_start = " ";
                string del_end = " ";
                if (v == pos.v && h == pos.h)
                {
                    del_start = "[";
                    del_end = "]";
                }
                cout << del_start << this->GetMapScoreByPosition(Position(v, h)) << del_end;
            }
            cout << '\n';
        }
        return;
    }
#endif
private:
    vector<vector<ScoreType>> map_scores;
};

class Game
{
public:
    Game(Map* map, Dice* dice):
        map(map), dice(dice)
    {};
public:
    void CalculateScore(CountType& moving_count) 
    {
#ifdef DEBUG
        cout << "=== INITIAL STATE ===\n";
        map->PrintMapWithPosition(dice->GetPosition());
        dice->PrintDice();
        cout << '\n';
#endif
        for (CountType c = 0; c < moving_count; ++c)
        {
            /// (1) MOVE DICE
            Dice tdice(*this->dice);
            tdice.Roll();
            /// 주사위를 임시로 미리 굴려보고, 굴릴 수 없으면 방향을 역전(Invert)시킨다.
            if (!this->IsInMapBound(tdice.GetPosition()))
                this->dice->InvertDirection();
            this->dice->Roll();

            /// (2) CALCULATE SCORE
            const Position& dice_pos = this->dice->GetPosition();
            const ScoreType& map_score = this->map->GetScoreByPosition(dice_pos);
            const CountType same_count = this->map->GetAdjacentSameScoreCounts(dice_pos);

            this->total_score += map_score * same_count;

            /// (3) SET DIRECTION
            const ScoreType& A = this->dice->GetBottomScore();
            const ScoreType& B = map_score;
            if (A > B)
                this->dice->RotateDirectionC90();
            else if (A < B)
                this->dice->RotateDirectionCC90();
            else /* Do Nothing */;
#ifdef DEBUG
            cout << "=== MovingNumber(" << c + 1 << ")===\n";
            map->PrintMapWithPosition(dice->GetPosition());
            dice->PrintDice();
            cout << "- DicePosition: " << "(" << dice->GetPosition().v <<"/" << this->map->GetVSize() - 1 << ", " << dice->GetPosition().h << "/" << this->map->GetHSize() - 1 << ")\n";
            cout << "- DiceRollDirection: " << dice->GetDirectionString() << '\n';
            cout << "- A-dbottom(" << A << "), B-mapscore(" << B << ")\n\n";
#endif
        }
        return;
    };
    ScoreType GetTotalScore() const { return this->total_score; };
public:
    bool IsInMapBound(const Position& pos) const { return this->map->IsInBound(pos); };
private:
    Map* map;
    Dice* dice;
    ScoreType total_score = 0;
};

int main()
{
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr); std::cout.tie(nullptr);
    }

    /// === INPUT === ///
    SizeType map_v_size; cin >> map_v_size; //<  [2, 20]
    SizeType map_h_size; cin >> map_h_size; //<  [2, 20]
    CountType moving_count; cin >> moving_count; //< [1, 1e3]

    vector<vector<ScoreType>> tmap_scores(map_v_size, vector<ScoreType>(map_h_size));

    for (SizeType v = 0; v < map_v_size; ++v)
        for (SizeType h = 0; h < map_h_size; ++h)
            cin >> tmap_scores[v][h]; // [1, 10] Natural Number

    /// === PROCESS === ///
    Map map(tmap_scores); Dice dice;
    Game game(&map, &dice);
    game.CalculateScore(moving_count); //< 대부분의 로직이 여기에 있음

    /// === OUTPUT === ///
    cout << game.GetTotalScore() << '\n';

    return 0;
}

