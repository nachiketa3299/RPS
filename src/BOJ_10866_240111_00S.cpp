// title: 백준 10866 덱 S4
// date: 15:25 16:55 90
// 이중 연결 리스트로 덱을 구현하는 문제. 시간을 단축시킬 수 있다면 좋을듯.
// 스태틱 맵 관련해서 애를 먹었는데 C++17 에서 되는지 다시 한번 확인해봐야함.
#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
enum Type {
    Push_Front, Push_Back, Pop_Front, Pop_Back,
    Size, Empty, Front, Back,
    Error
};

class Command {
public:
    Command(): command_str_(""), arg_(0), has_arg_(false), type_(Error) {};
    friend istream& operator>>(istream& is, Command& command) {
        static const auto& ctot = Command::CreateMap();
        is >> command.command_str_;
        command.type_ = ctot.at(command.command_str_);
        switch(command.type_) {
            case Push_Front:
            case Push_Back:
                command.has_arg_ = true;
                is >> command.arg_;
                break;
            default:
                break;
        }
        return is;
    }
    inline bool HasArg() const {
        return has_arg_;
    }
    inline const int& arg() const {
        return arg_;
    }
    inline const Type& type() const {
        return type_;
    }
private:
    string command_str_;
    Type type_;
    int arg_;
    bool has_arg_;
public:
    inline static map<string, Type> CreateMap() {
        return map<string, Type> {
            { "push_back", Push_Back }, { "push_front", Push_Front }, { "pop_back", Pop_Back }, { "pop_front", Pop_Front },
            { "size", Size }, { "empty", Empty }, { "front", Front }, { "back", Back }
        };
    }
};

struct Node {
    Node(int ival): val(ival), next(nullptr), prev(nullptr) {};
    int val;
    Node* next;
    Node* prev;
};

class IntDeque {
public:
    IntDeque(): sn_(0), front_(&sn_), back_(&sn_), size_(0) {
        sn_.prev = &sn_;
        sn_.next = &sn_;
    };
public:
    void ProcessCommands(const Command& command) {
        switch(command.type()) {
            case Push_Front:
                PushFront(command.arg());
                break;
            case Push_Back:
                PushBack(command.arg());
                break;
            case Pop_Front:
                cout << PopFront() << '\n';
                break;
            case Pop_Back:
                cout << PopBack() << '\n';
                break;
            case Front:
                cout << GetFront() << '\n';
                break;
            case Back:
                cout << GetBack() << '\n';
                break;
            case Empty:
                cout << IsEmpty() << '\n';
                break;
            case Size:
                cout << GetSize() << '\n';
                break;
            default:
                cout << "Error!" << '\n';
                break;
        }
    }
    void PushFront(const int& val) {
        auto* to_push = new Node(val);
        auto* past_front = sn_.next;
        sn_.next = to_push;
        to_push->next = past_front;
        to_push->prev = &sn_;
        past_front->prev = to_push;
        size_++;
    }
    void PushBack(const int& val) {
        auto* to_push = new Node(val);
        auto* past_back = sn_.prev;
        sn_.prev = to_push;
        to_push->next = &sn_;
        to_push->prev = past_back;
        past_back->next = to_push;
        size_++;
    }
    int PopFront() {
        if (IsEmpty())
            return -1;
        const auto ret = GetFront();
        auto* to_pop = sn_.next;

        auto* sn_nn = sn_.next->next;

        sn_.next = sn_nn;
        sn_nn->prev = &sn_;

        delete to_pop;
        size_--;
        return ret;
    }
    int PopBack() {
        if (IsEmpty())
            return -1;
        const auto ret = GetBack();
        auto* to_pop = sn_.prev;
        auto* sn_pp = sn_.prev->prev;

        sn_.prev = sn_pp;
        sn_pp->next = &sn_;

        delete to_pop;
        size_--;
        return ret;
    }
    inline int GetFront() const {
        if (IsEmpty())
            return -1;
        return sn_.next->val;
    }
    inline int GetBack() const {
        if (IsEmpty())
            return -1;
        return sn_.prev->val;
    }
    inline size_t GetSize() const {
        return size_;
    }
    inline bool IsEmpty() const {
        if (sn_.next == &sn_ && sn_.prev == &sn_)
            return true;
        else 
            return false;
    }
private:
    Node* front_;
    Node* back_;
    Node sn_;
    size_t size_;
};

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int N; cin >> N; const int& command_size = N; // [1, 1e4]
    vector<Command> commands(N);
    for_each(commands.begin(), commands.end(), [](auto& command) {cin >> command;} );

    IntDeque deque;
    for_each(commands.cbegin(), commands.cend(), [&deque](const auto& command) { deque.ProcessCommands(command); });

    
    return 0;
}