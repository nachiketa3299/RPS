/*!
* @file BOJ_20055_231206.cpp
* @date 2023-12-06 T 16:35
* 백준 20055 컨베이어 벨트 위의 로봇 G5
* 1초, 512MB
*/

/*!
* 길이가 N인 컨베이어 벨트가 있고, 길이가 2N인 벨트가 이 컨베이어 벨트를 위아래로 감싸고 돌고 있다.
* 벨트는 길이 1 간격으로 2N개의 칸으로 나뉘어 있다.
* 각 칸에는 다음처럼 1 ~ 2N 까지의 번호가 매겨져 있다.
* ->
* | 1**  | 2    | 3    |  ... | N-1  | N** |
* | 2N   | 2N-1 | 2N-2 |  ... | N+1  | N+1 |
* <-
* 벨트가 한 칸 회전하면 1 ~ 2N-1 번째 칸은 다음 칸의 위치로 이동하고, 2N번 칸은 1번 칸의 위치로 이동한다.
* i번 칸의 내구도는 A_i이다.
* 1번 칸의 위치를 *올리는 위치*, N번 칸의 위치를 *내리는 위치*라고 한다.
* 
* *올리는 위치* 에 박스 모양 로봇을 하나씩 올리려고 한다.
* 언제든지 로봇이 *내리는 위치*에 도달하면 즉시 내린다.
* 로봇은 벨트 위에서 스스로 이동할 수 있다.
* 로봇을 *올리는 위치*에 올리거나, 로봇이 어떤 칸으로 이동하면 그 칸의 내구도는 즉시 1만큼 감소한다.
* 
* 컨베이어 벨트를 이용해 로봇을 건너편으로 옮기려고 한다.
* 옮기는 과정에서 다음의 일이 순서대로 일어난다.
* (1) 벨트가 각 칸위에 있는 로봇과 함께 한 칸 회전한다.
* (2) 가장 먼저 벨트에 올라간 로봇부터, 벨트가 회전하는 방향으로 한 칸 이동할 수 있다면 이동한다.
*     만일 이동할 수 없다면, 가만히 있는다.
*       로봇이 이동하려면 이동하려는 칸에 로봇이 없으며, 그 칸에 내구도가 1 이상 남아있어야 한다.
* (3) *올리는 위치*에 있는 칸의 내구도가 0이 아니면, 올리는 위치에 로봇을 올린다.
* (4) 내구도가 0인 칸의 갯수가 K개 이상이면, 과정을 종료한다. 그렇지 않으면 1번으로 돌아간다.
* 
* 과정이 종료되었을 때, 몇 번째 단계가 진행 중이었는지 구한다.
* 가장 처음 수행되는 단계는 (1) 번째 단계이다.
*/
#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;
#define IS_STOPPED bool
#define NOT_STOPPED false
#define STOPPED true

class Conveyer
{
public:
    struct Node
    {
        Node(int durability):durability(durability) {};
        Node* next = nullptr;
        Node* prev = nullptr;
        int durability;
        bool occupied = false;
#ifdef PS_DEBUG
        int id;
#endif

    };
public:
    Conveyer(int N, int K): size(2 * N), robot_pos(0), K(K)
    {
        std::vector<Node*> nodes(2 * N);

        for (size_t i = 0; i < 2 * N; ++i)
        {
            int durability; cin >> durability;
            nodes[i] = new Node(durability);
#ifdef PS_DEBUG
            nodes[i]->id = i + 1;
#endif 
        }

        this->ptr_push = nodes[0];
        this->ptr_pop = nodes[N - 1];

        for (size_t i = 0; i < nodes.size(); ++i)
        {
            if (i == 0)
            {
                nodes[i]->prev = nodes[2 * N - 1];
                nodes[i]->next = nodes[i + 1];
            }
            else if (i == nodes.size() - 1)
            {
                nodes[i]->prev = nodes[i - 1];
                nodes[i]->next = nodes[0];
            }
            else
            {
                nodes[i]->prev = nodes[i - 1];
                nodes[i]->next = nodes[i + 1];
            }
        }
    };

    IS_STOPPED Move()
    {
        ptr_push = (ptr_push->prev);
        ptr_pop = (ptr_pop->prev);

        if (robot_pos.size() == 0)
            return NOT_STOPPED;

        if (robot_pos.front() == ptr_pop)
        {
            robot_pos.front()->occupied = false;
            robot_pos.pop_front();
        }

        return NOT_STOPPED;
    }

    IS_STOPPED ProceedRobots()
    {
        for (size_t i = 0; i < robot_pos.size(); ++i)
        {
            // 지금 내리는 칸인지 확인한다
            if (robot_pos.at(i) == ptr_pop)
            {
                robot_pos.at(i)->occupied = false;
                assert(robot_pos.at(i) == robot_pos.front());
                robot_pos.pop_front();
                continue;
            }

            // 앞 칸에 누가 있다면 못 움직임
            if (robot_pos.at(i)->next->occupied) continue;
            // 앞 칸에 내구도가 0이면 못 움직임
            if (robot_pos.at(i)->next->durability == 0) continue;

            // 앞 칸 으로 움직일 수 있는 상황
             
            // 움직이고 나면 occupy 상황 처리 하고
            robot_pos.at(i)->occupied = false;
            robot_pos.at(i) = robot_pos.at(i)->next;
            robot_pos.at(i)->occupied = true;

            // 움직이면 내구도 수정 사건이 발생하므로 내구도 갯수 검사
            if (--robot_pos.at(i)->durability == 0)
            {
                ++durability_count;
                // 만일, 내구도가 기준치 이상이면 로직을 멈춤
                if (TestDurabilities() == STOPPED) 
                    return STOPPED;
            }

            // 여기까지 왔다는건 움직였는데, 내구도까지 처리했는데도 중단 안됐다는거
            // 근데 아직 움직인 칸이 내리는 칸인지 판단하는 과정이 남음

            // 움직이고 난 칸이 내리는 칸이면 내린다. occupy 상황 처리
            if (robot_pos.at(i) == ptr_pop)
            {
                assert(robot_pos.at(i) == robot_pos.front());
                robot_pos.at(i)->occupied = false;
                robot_pos.pop_front();
            }
        }
        return NOT_STOPPED;
    }

    IS_STOPPED PushRobot()
    {
        Node* current_push_pos = ptr_push;

        // 내구도 없으면 못올림
        if (ptr_push->durability == 0)
            return NOT_STOPPED;

        // 누가 있으면 못올림
        if (ptr_push->occupied)
            return NOT_STOPPED;

        // 올릴 수 있는 상황
        robot_pos.push_back(ptr_push);
        ptr_push->occupied = true;
        if (--ptr_push->durability == 0)
        {
            ++durability_count;
            if (TestDurabilities() == STOPPED)
                return STOPPED;
        }
        return NOT_STOPPED;
    }

    IS_STOPPED TestDurabilities() 
    {
        if (durability_count >= K) return STOPPED;
        else return NOT_STOPPED;
    }

#ifdef PS_DEBUG
public:
    void PrintConveyer(int step_count) const
    {
        cout << "===Conveyer State "<< step_count << " ===\n";
        Node* i = ptr_push;

        for (size_t n = 0; n < size; ++n)
        {
            string pad;
            if (i->id <= 9) pad = "  ";
            else if (i->id <= 99) pad = " ";
            else if (i->id <= 999) pad = "";

            cout << pad << i->id;
            if (i == ptr_pop) cout << "||";
            else cout << "|";
            i = i->next;
        }
        cout << '\n';
        for (size_t n = 0; n < size; ++n)
        {
            string pad;
            if (i->durability <= 9) pad = "  ";
            else if (i->durability <= 99) pad = " ";
            else if (i->durability <= 999) pad = "";

            cout << pad << i->durability;
            if (i == ptr_pop) cout << "||";
            else cout << "|";
            i = i->next;
        }
        cout << '\n';
        for (size_t n = 0; n < size; ++n)
        {
            string pad = "   ";
            if (i->occupied) pad = "  R";

            cout << pad;
            if (i == ptr_pop) cout << "||";
            else cout << "|";
            i = i->next;
        }
        
        cout << "\n\n";
    }
#endif //!PS_DEBUG
public:
    Node* ptr_push = nullptr;
    Node* ptr_pop = nullptr;
    deque<Node*> robot_pos;
    int size;
    int durability_count = 0;
    int K;
};


class Director
{
public:
    Director(Conveyer* conv): conv(conv) {};
    int Process() 
    {
        static int step_count = 0;
        while (true)
        {

#ifdef PS_DEBUG
            conv->PrintConveyer(step_count);
#endif // PS_DEBUG
            ++step_count;
            if (conv->Move() == STOPPED) break;
#ifdef PS_DEBUG
            cout << "== After Move\n";
            conv->PrintConveyer(step_count);
#endif // PS_DEBUG
            if (conv->ProceedRobots() == STOPPED) break;
#ifdef PS_DEBUG
            cout << "== After Proceeding Robots\n";
            conv->PrintConveyer(step_count);
#endif // PS_DEBUG
            if (conv->PushRobot() == STOPPED) break;
#ifdef PS_DEBUG
            cout << "== After Pushing Robot\n";
            conv->PrintConveyer(step_count);
            cout << "=========================\n";
#endif // PS_DEBUG

        };

        return step_count;
    }
private:
    Conveyer* conv;
};

#ifdef PS_DEBUG
#include <fstream>
#endif


int main(void)
{
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr); std::cout.tie(nullptr);
    }

#ifdef PS_DEBUG
        std::ofstream out("BOJ_20055_231206_out.txt");
        std::streambuf* counbuf = std::cout.rdbuf();
        std::cout.rdbuf(out.rdbuf());
#endif

    int N; cin >> N; // [1, 100]
    int K; cin >> K; // [1, 2N]

    Director director(new Conveyer(N, K));
    cout << director.Process() << '\n';
    return 0;
}