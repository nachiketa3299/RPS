/*!
* @file BOJ_20055_231206_01.cpp
*/
#include <deque>


#define PS_DEBUG
//#undef PS_DEBUG
#define PS_COUT_TO_FILE
//#undef PS_COUT_TO_FILE

#include <iostream>
#include <vector>
#include <cassert>

#ifdef PS_COUT_TO_FILE
#include <fstream>
#endif

#define INDEX_ROBOT_PUSH 0
#define INDEX_ROBOT_POP(ConveyerSize) ((ConveyerSize / 2) - 1)


using namespace std;

struct Node;

struct Robot
{
#ifndef PS_DEBUG
    Robot(Node* PushPosition): On(PushPosition) {};
#endif //!PS_DEBUG
#ifdef PS_DEBUG
    Robot(Node* PushPosition, int UniqueIndex): On(PushPosition), UniqueIndex(UniqueIndex) {};
#endif
    Node* On;
    Robot* Next;
#ifdef PS_DEBUG
    int UniqueIndex = 0;
#endif //PS_DEBUG
};

class RobotList
{
public:
    void Push(Robot* NewRobot)
    {
        if (Size == 0)
        {
            Head = NewRobot;
            Tail = NewRobot;
            return;
        }

        Robot* PrevTail = Tail;
        Tail = NewRobot;
        PrevTail->Next = Tail;
        ++Size;
    };
    void Pop()
    {
        assert(Size != 0);
        Robot* PrevHead = Head;
        Head = Head->Next;
        return;
    }
    inline Robot* GetHeadRobot() const { return Head; };
    inline Robot* GetTailRobot() const { return Tail; };
    inline int GetSize() const { return Size; };
private:
    int Size = 0;
    Robot* Head = nullptr;
    Robot* Tail = nullptr;
};

struct Node
{
public:
    Node(int Durability): Durability(Durability) {};
    inline bool IsOccupiedByRobot() const { return (Robot ? true : false); };
    inline bool HasDurability() const { return (Durability >= 0); };
    inline void DecreaseDurability() { --Durability; };
    inline void DiscardRobot() { delete Robot; }
public:
    Robot* Robot = nullptr;
    Node* Next = nullptr;
    Node* Prev = nullptr;
    int Durability;
#ifdef PS_DEBUG
    int UniqueIndex = 0;
#endif //PS_DEBUG
};


class Conveyer
{
public:
    enum Signal { Success, Failed };
public:
    Conveyer(int HalfSize, int DurabilityCountMax):
        Size(2 * HalfSize), DurabilityCountMax(DurabilityCountMax)
    {
        // 동적 할당을 및 입력 위한 노드 임시 벡터 생성
        vector<Node*> TempNodes(Size);
        for (auto& TempNode : TempNodes)
        {
            int Durability; cin >> Durability;
            TempNode = new Node(Durability);
#ifdef PS_DEBUG
            TempNode->UniqueIndex = &TempNode - &TempNodes[0];
#endif //PS_DEBUG
        }

        // 올려두는 곳과 내려두는 곳을 설정함
        RobotPushPosition = TempNodes[INDEX_ROBOT_PUSH];
        RobotPopPosition = TempNodes[INDEX_ROBOT_POP(Size)];

        // 컨베이어 벨트 링크를 구축함
        for (size_t i = 0; i < Size; ++i)
        {
            if (i == INDEX_ROBOT_PUSH)
            {
                TempNodes[i]->Prev = TempNodes[INDEX_ROBOT_POP(Size)];
                TempNodes[i]->Next = TempNodes[i + 1];
            }
            else if (i == INDEX_ROBOT_POP(Size))
            {
                TempNodes[i]->Prev = TempNodes[i - 1];
                TempNodes[i]->Next = TempNodes[INDEX_ROBOT_PUSH];
            }
            else
            {
                TempNodes[i]->Prev = TempNodes[i - 1];
                TempNodes[i]->Next = TempNodes[i + 1];
            }
        }

        return;
    };
public:
    Signal Move()
    {
        RobotPushPosition = (RobotPushPosition->Prev);
        RobotPopPosition = (RobotPopPosition->Prev);

        if (!RobotPopPosition->IsOccupiedByRobot())
            return Success;

        AllRobots.Pop();
        RobotPopPosition->DiscardRobot();
        return Success;
    }
    Signal ProcceedRobots()
    {
        Robot* it = AllRobots.GetHeadRobot();
        for (size_t i = 0; i < AllRobots.GetSize(); ++i)
        {
            if (it->On->Next->IsOccupiedByRobot())
                continue;
            if (!it->On->Next->HasDurability())
                continue;

            if (it->On->Next == RobotPopPosition)
            {
            }
        }
    }
    Signal PushRobot() 
    {
        if (RobotPushPosition->IsOccupiedByRobot())
        {
            return Success;
        }

        if (!RobotPushPosition->HasDurability())
        {
            return Success;
        }

        // 여기부터는 로봇을 실제로 올리고, 내구도를 감소시킴

#ifndef PS_DEBUG
        RobotPushPosition->Robot = new Robot(RobotPushPosition);
#endif //!PS_DEBUG
#ifdef PS_DEBUG
        static int RobotUniqueIndex = 0;
        RobotPushPosition->Robot = new Robot(RobotPushPosition, RobotUniqueIndex++);
#endif //PS_DEBUG

        AllRobots.Push(RobotPushPosition->Robot);

        return DecreaseNodeDurabilityAndReturnVerifySignal(*RobotPushPosition);
    };

    Signal DecreaseNodeDurabilityAndReturnVerifySignal(Node& TargetNode) 
    {
        TargetNode.DecreaseDurability();
        if (!TargetNode.HasDurability())
        {
            return TestDurabilityLimit() ? Success : Failed;
        }
        return Success;
    };

    inline bool TestDurabilityLimit() const { return (DurabilityCount >= DurabilityCountMax); };
private:
    Node* RobotPushPosition;
    Node* RobotPopPosition;
    int Size;
    int DurabilityCount = 0;
    int DurabilityCountMax;
    RobotList AllRobots;
};

class Manager
{
public:
    using ConveyerSignal = Conveyer::Signal;
public:
    Manager(Conveyer* Conv): Conv(Conv) {};
public:
    void ProcessUntilStopped(int& OutStepCount)
    {
        OutStepCount = 0;
        while (true)
        {
            ++OutStepCount;
            if (Conv->Move() == ConveyerSignal::Failed)
                break;
            if (Conv->ProcceedRobots() == ConveyerSignal::Failed)
                break;
            if (Conv->PushRobot() == ConveyerSignal::Failed)
                break;
        }
        return;
    }
private:
    Conveyer* Conv;
};

int main()
{
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr); std::cout.tie(nullptr);
    }
#ifdef PS_COUT_TO_FILE
    std::ofstream out("BOJ_20055_231206_out.txt");
    std::streambuf* counbuf = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());
#endif //PS_COUT_TO_FILE

    int N; cin >> N; // [1, 100]
    int K; cin >> K; // [1, 2N]

    Manager Man(new Conveyer(N, K));

    int StepCount;
    Man.ProcessUntilStopped(StepCount);

    cout << StepCount << '\n';

    return 0;
}