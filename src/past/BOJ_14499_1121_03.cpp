/// @file BOJ_14499.cpp
/// @date 2023-11-21 T 21:28 23:06

/// 크기가 N x M인 지도가 존재
/// 우측이 동쪽, 위쪽이 북쪽
/// 지도 위에 주사위 하나 전개도는 아래와 같다.
/*!
*  2
* 413
*  5
*  6
*/
/// 지도의 좌표는 (r, c)로 나타내며, r은 북쪽으로부터 떨어진 칸의 갯수, c는 서쪽으로부터 떨어진 칸의 갯수이다.
/// 주사위는 지도 위에 윗면이 1, 동쪽을 바라보는 방향이 3인 상태로 처음에 놓여져 있으며, 놓인 좌표는 (x, y)이다.
/// 가장 처음에 주사위의 모든 면에는 0이 적혀져 있다.
/// 지도의 각 칸에는 정수가 하나씩 쓰여 있다.
/// 주사위 굴렸을 때, 이동한 칸에 쓰여 있는 수가 0이면, 주사위의 바닥면에 쓰여 있는 수가 칸에 복사된다.
/// 이동한 칸에 쓰여 있는 수가 0이 아니면, 칸에 쓰여있는 수가 주사위의 바닥면으로 복사되며, 지도 칸에 쓰여 있는 수는 0이 된다.
/// 
/// 주사위를 놓은 곳의 좌표와 이동시키는 명령이 주어졌을 때, 주사위가 이동했을 때마다 상단에 쓰여 있는 값을 구하는 프로그램을 작성한다.
/// 주사위는 지도의 바깥으로 이동시킬 수 없다. 만약 바깥으로 이동시키려고 하는 경우, 해당 명령을 무시하며 출력도 안한다.
/// 

#include <iostream>
#include <vector>
#include <utility>
#include <array>

using namespace std;
/// @short 지도의 크기
using SizeType = size_t;
using CountType = size_t;
using IndexType = int;
/// @short 지도의 각 칸에 쓰여 있는 수 [0, 10) 인 정수
using ScoreType = int;
using DiceSideScores = array<ScoreType, 6>;

enum class Command
{
    EAST=1, WEST, NORTH, SOUTH
};
istream& operator>>(istream& is, Command& command)
{
    int t; is >> t;
    switch(t) 
    { 
        default: 
        case 1: command = Command::EAST; break;
        case 2: command = Command::WEST; break;
        case 3: command = Command::NORTH; break;
        case 4: command = Command::SOUTH; break;
    }
    return is;
}

struct Position
{
    IndexType x = 0;
    IndexType y = 0;
    void MovePositionByCommand(const Command& command)
    {
        switch (command)
        {
            default:
            case Command::EAST: ++this->y; break;
            case Command::WEST: --this->y; break;
            case Command::NORTH: --this->x; break;
            case Command::SOUTH: ++this->x; break;
        }
        return;
    }
};

enum  DiceSide
{
    DS_LEFT=0, DS_RIGHT, DS_UP, DS_DOWN, DS_TOP, DS_BOTTOM
};


class Dice
{
public:
    Dice() = default;
    Dice(IndexType x, IndexType y): position {x, y} 
    {
        this->dice_scores.fill(0);
        return;
    }
    Position GetPosition() const
    {
        return this->position;
    }
    void SetPosition(const Position& position)
    {
        this->position = position;
        return;
    }
    void RollDiceByCommand(const Command& command)
    {
        auto temp = this->dice_scores[DS_BOTTOM];
        switch (command)
        {
        default:
        case Command::EAST: 
            /// B -> L
            this->dice_scores[DS_BOTTOM] = this->dice_scores[DS_LEFT];
            /// L -> T
            this->dice_scores[DS_LEFT] = this->dice_scores[DS_TOP];
            /// T -> R
            this->dice_scores[DS_TOP] = this->dice_scores[DS_RIGHT];
            /// R -> B
            this->dice_scores[DS_RIGHT] = temp;
            break;
        case Command::WEST: 
            /// B -> R
            this->dice_scores[DS_BOTTOM] = this->dice_scores[DS_RIGHT];
            /// R -> T
            this->dice_scores[DS_RIGHT] = this->dice_scores[DS_TOP];
            /// T -> L
            this->dice_scores[DS_TOP] = this->dice_scores[DS_LEFT];
            /// L -> B
            this->dice_scores[DS_LEFT] = temp;
            break;
        case Command::NORTH: 
            /// B -> D
            this->dice_scores[DS_BOTTOM] = this->dice_scores[DS_DOWN];
            /// D -> T
            this->dice_scores[DS_DOWN] = this->dice_scores[DS_TOP];
            /// T -> U
            this->dice_scores[DS_TOP] = this->dice_scores[DS_UP];
            /// U -> B
            this->dice_scores[DS_UP] = temp;
            break;
        case Command::SOUTH: 
            /// B -> U
            this->dice_scores[DS_BOTTOM] = this->dice_scores[DS_UP];
            /// U -> T
            this->dice_scores[DS_UP] = this->dice_scores[DS_TOP];
            /// T -> D
            this->dice_scores[DS_TOP] = this->dice_scores[DS_DOWN];
            /// D -> B
            this->dice_scores[DS_DOWN] = temp;
            break;
        }
        return;
    }
    ScoreType GetBottomScore() const { return this->dice_scores[DS_BOTTOM]; };
    void SetBottomScore(ScoreType score) { this->dice_scores[DS_BOTTOM] = score; };
    ScoreType GetTopScore() const { return this->dice_scores[DS_TOP]; };
private:
    void SwapSides(DiceSide from, DiceSide to)
    {
        ScoreType temp = this->dice_scores[from];
        this->dice_scores[from] = this->dice_scores[to];
        this->dice_scores[to] = temp;
        return;
    }
private:
    Position position;
    DiceSideScores dice_scores;
};

class Map
{
public:
    Map(SizeType N, SizeType M): map_scores(N, vector<ScoreType>(M)) 
    {
        for (vector<ScoreType>& row : map_scores)
            for (ScoreType& element : row)
                cin >> element;
        return;
    };
    bool IsPositionInBoundary(const Position& position) const
    {
        return this->IsPositionInBoundary(position.x, position.y);
    }
    bool IsPositionInBoundary(SizeType x, SizeType y) const
    {
        bool is_in_x_boundary = x < map_scores.size() && x >= 0;
        bool is_in_y_boundary = y < map_scores.front().size() && y >= 0;
        
        return is_in_x_boundary && is_in_y_boundary;
    }
    ScoreType GetScore(const Position& position) const
    {
        return this->GetScore(position.x, position.y);
    }
    ScoreType GetScore(SizeType x, SizeType y) const
    {
        return this->map_scores[x][y];
    }
    void SetScore(const Position& position, ScoreType score)
    {
        this->SetScore(position.x, position.y, score);
        return;
    }
    void SetScore(SizeType x, SizeType y, ScoreType score)
    {
        this->map_scores[x][y] = score;
        return;
    }

private:
    vector<vector<ScoreType>> map_scores;
};

class Game
{
public:
    Game(Map& map, Dice& dice, vector<Command> commands): 
        map(move(map)),
        dice(move(dice)),
        commands(move(commands))
    {};
    void ProcessCommands()
    {
        for (const Command& command : commands)
        {
            Position current_position = (this->dice).GetPosition();
            current_position.MovePositionByCommand(command);

            if (!this->map.IsPositionInBoundary(current_position))
                continue;

            this->dice.RollDiceByCommand(command);

            const ScoreType& map_pos_score = this->map.GetScore(current_position);
            const ScoreType& dice_bottom_score = this->dice.GetBottomScore();

            if (map_pos_score == 0)
            {
                this->map.SetScore(current_position, dice_bottom_score);
            }
            else
            {
                this->dice.SetBottomScore(map_pos_score);
                this->map.SetScore(current_position, 0);
            }

            this->dice.SetPosition(current_position);

            cout << dice.GetTopScore() << '\n';
        }
        return;
    }
private:
    Dice dice;
    Map map;
    vector<Command> commands;
};


int main()
{
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr); std::cout.tie(nullptr);
    }

    // INPUT N, M
    SizeType N; cin >> N;
    SizeType M; cin >> M;

    // INPUT x, y
    IndexType x; cin >> x;
    IndexType y; cin >> y;
    Dice dice(x, y);

    // INPUT K
    CountType K; cin >> K;

    // INPUT Map Scores
    Map map(N, M);

    // INPUT Commands;
    vector<Command> commands(K); 
    for (Command& command : commands) cin >> command;

    Game game(map, dice, commands);
    game.ProcessCommands();

    return 0;
}
