/*!
* @file BOJ_1717_231205.cpp
* @date 2023-12-05T10:29 11:30 대충 50분 걸림
* 백준 1717 집합의 표현 G5
* 2초, 128MB
*/

/*!
* 초기에 \f$n+1\f$ 개 집합 \f$\{0\}, \{1\}, ..., \{n\}\f$이 있다.
* 여기에 합집합 연산과, 두 원소가 같은 집합에 포함되어 있는지 확인하는 연산을 수행하려고 한다.
* 집합을 표현하는 프로그램을 작성한다.
*/

#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <vector>

#ifdef PS_DEBUG
#include <string>
#endif

using namespace std;

/// Type Alias
using CountType = size_t;
using OperandType = size_t;
using IndexType = size_t;

/*!
* @enum Operation
* @brief 연산의 종류를 나타내는 열거형
*/
enum Operation 
{ 
    Union = 0,  //< 합집합 연산(0)
    Membership  //< 포함 여부를 확인하는 연산(1)
};

/// @struct Command
/// @short 명령어와 연산자를 저장하는 구조체
struct Command
{
    Command(const Operation& opcode, const OperandType& op1, const OperandType op2): opcode(opcode), op1(op1), op2(op2) {};

    /// @short 연산의 종류
    Operation opcode;
    /// @short 피연산자 1
    OperandType op1;
    /// @short 피연산자 2
    OperandType op2;

#ifdef PS_DEBUG
    string GetCommandString() const
    {
        string op_str = (opcode == Union) ? "UNION" : "MEMBE";
        return op_str + " " + to_string(this->op1) + " " + to_string(this->op2);
    }
#endif
};

#define OP_ERROR false
#define OP_UNI_SUCCESS true
#define OP_UNI_IGNORE false
#define OP_MEM_IN true
#define OP_MEM_NOT_IN false

/*!
* @class Set
* @brief 커스텀 집합 컨테이너 클래스
*/
class Sets
{
public:
    /// @short 문제의 초기 설정대로 @p size + 1 개의 집합을 만듦
    Sets(const CountType& size): parents(size + 1)
    {
        /// 초기 상태에서 모두 분할되어 있으므로 각자의 부모는 자기 자신으로 설정한다
        /// @warning 0 부터 n 까지 총 **n + 1** 개의 원소가 존재함
        for (IndexType i = 0; i < size + 1; ++i)
            this->parents[i] = i;
        return;
    };

    /// @short @p command 의 종류에 따라 내부 연산을 실행
    bool Operation(const Command& command) 
    {

#ifdef PS_DEBUG
        cout << "= Processing Operation: " << command.GetCommandString() << '\n';
        cout << "- Current State:\n";
        this->PrintParents();
#endif // PS_DEBUG

        switch (command.opcode)
        {
        case Union:         return this->Op_Union(command.op1, command.op2);
        case Membership:    return this->Op_Membership(command.op1, command.op2);
        default:            break;
        }
        return OP_ERROR;
    };

    /*!
     * @brief @p op1 과 @p op2 가 같은 집합에 속하는지 확인
     * @return 같은 집합에 속하면 true, 아니면 false
    */
    bool Op_Membership(const OperandType& op1, const OperandType& op2) const
    {
        if (op1 == op2) 
            return OP_MEM_IN;
        if (this->GetRootParent(op1) == this->GetRootParent(op2)) 
            return OP_MEM_IN;
        else 
            return OP_MEM_NOT_IN;
    }

    /*!
     * @brief @p op1 가 포함된 집합과 @p op2 가 포함된 집합을 (합칠 필요가 있다면) 합친다. 
     * @return 합집합 연산이 무시되거나 오류인 경우 false, 합집합 연산이 수행되었다면 true
     * @pre @ref Op_Membership(const OperandType&, const OperandType&)
    */
    bool Op_Union(const OperandType& op1, const OperandType& op2)
    {
        // 애초에 op1과 op2가 같으면 합칠 필요가 없다.
        if (op1 == op2) 
            return OP_UNI_IGNORE;
        // 애초에 op1과 op2가 같은 집합에 속해 있으면 합칠 필요가 없다.
        if (this->Op_Membership(op1, op2))
            return OP_UNI_IGNORE;

        // 각 집합의 대표를 가져옴 (최상위 부모 노드)
        const IndexType op1_root = this->GetRootParent(op1);
        const IndexType op2_root = this->GetRootParent(op2);

        // 더 작은 놈이 위로 가게 부모를 재할당한다.
        // 이 부분에서 op1_root와 op2_root가 같은 경우는 없음
        if (op1_root > op2_root)
        {
            this->parents[op1_root] = op2_root;
            return OP_UNI_SUCCESS;
        }
        else
        {
            this->parents[op2_root] = op1_root;
            return OP_UNI_SUCCESS;
        }

        return OP_ERROR;
    }

    /// @short 각 @p index 번 집합의 대표(최상위 부모 노드)를 가져온다.
    IndexType GetRootParent(const IndexType& index) const
    {
        const IndexType& current_parent = this->parents[index];
        if (current_parent == index) return index;
        return this->GetRootParent(current_parent);
    };
#ifdef PS_DEBUG
    void PrintParents() const
    {
        for (auto i = 0; i < this->parents.size(); ++i)
            cout << i << "[" << this->parents[i] << "] ";
        cout << '\n';
        return;
    }
#endif
public:
    /// @short 집합별로 부모를 기록하는 멤버
    vector<IndexType> parents;
};


int main(void)
{
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr); std::cout.tie(nullptr);
    }

    /*!
    * @var n
    * @brief 집합의 초기 갯수
    * @note [1, 1e6]
    * @details {0}, {1}, ..., {n} 까지 총 n+1 개의 집합이 존재함
    */
    CountType n; cin >> n;
    /*!
    * @var m
    * @note [1, 1e5]
    * @brief 연산의 갯수
    */
    CountType m; cin >> m;

    vector<Command> commands;

    for (CountType command = 0; command < m; ++command)
    {
        int opcode; 
        /// a 와 b는 n 보다 작으며, 같을 수도 있다.
        OperandType a, b;
        cin >> opcode >> a >> b;
        commands.push_back(Command(static_cast<Operation>(opcode), a, b));
    }

#ifdef PS_DEBUG
    for (const auto& command : commands) { cout << command.GetCommandString() << '\n'; }
#endif

    Sets set(n);
    for (const auto& command : commands)
    {
        /// 멤버십만 뭘 출력하므로 나눠줘야함
        if (command.opcode == Membership)
        {
            string mem_result_string = set.Operation(command) ? "YES" : "NO";
            cout << mem_result_string << '\n';
        }
        else set.Operation(command);

    }

    return 0;
}

