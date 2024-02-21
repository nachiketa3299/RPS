#include <iostream>
#include <string>

namespace cmddata {
    enum cmdcode { PUSH, POP, SIZE, EMPTY, FRONT, BACK };
    cmddata::cmdcode strToCommand(std::string cmd_str) {
        using namespace cmddata;
        if      (cmd_str == "push")  return PUSH;
        else if (cmd_str == "pop")   return POP;
        else if (cmd_str == "size")  return SIZE;
        else if (cmd_str == "empty") return EMPTY;
        else if (cmd_str == "front") return FRONT;
        else                         return BACK;
    }

    class Command {
    private:
        cmddata::cmdcode command;
        int arg;
    public:
        Command(const std::string cmd_str) {
            int parse_idx = cmd_str.find(' ');
            if (parse_idx != std::string::npos) {
                this->command = strToCommand(cmd_str.substr(0, parse_idx));
                this->arg = std::stoi(cmd_str.substr(parse_idx + 1));
            } else {
                this->command = strToCommand(cmd_str);
                this->arg = -1;
            }
        }
        int getArg(void) const { 
            return this->arg; 
        }
        cmddata::cmdcode getCommandCode(void) const { 
            return this->command; 
        }
    };
}


class Queue {
private:
    struct Node {
        int value;
        Node *prev, *next;
        Node(int value=0): value(value), prev(nullptr), next(nullptr) {}
    };
    enum STATE { QUEUE_IS_EMPTY=-1 };
    // Actual Members
    Node *sn; // Sentinel Node of Queue
    std::size_t size;
public: // Constructor & Destructor
    Queue(void): sn(new Node()), size(0) {
        this->sn->next = this->sn;
        this->sn->prev = this->sn;
        return;
    }
    ~Queue(void) {
        delete sn;
        return;
    }
public: // Member Function for PS
    void push(int value) {
        ++this->size;
        Node *to_push = new Node(value);
        Node &sent = *(this->sn);
        Node &rear = *(this->sn->prev);
        sent.prev = to_push;
        to_push->next = &sent;
        rear.next = to_push;
        to_push->prev = &rear;
    }
    int pop(void) {
        if (this->empty()) return QUEUE_IS_EMPTY;
        else {
            --this->size;

            Node &sent = *(this->sn);
            Node &pop_target = *(this->sn->next);
            int pop_val = pop_target.value;
            Node &head_next = *(this->sn->next->next);
            sent.next = &head_next;
            head_next.prev = &sent;

            delete &pop_target;

            return pop_val;
        }
    }

    std::size_t getSize(void) const {
        return this->size;
    }

    bool empty(void) const {
        return (this->size == 0 ? true : false);
    }

    int front(void) const {
        if (this->empty()) return QUEUE_IS_EMPTY;
        else return this->sn->next->value;
    }
    int back(void) const {
        if (this->empty()) return QUEUE_IS_EMPTY;
        else return this->sn->prev->value;
    }
};

class Handler {
private:
    Queue *queue;
public:
    Handler(void): queue(new Queue()) {}
    ~Handler(void) {
        delete this->queue;
        return;
    }
    void processCommand(const cmddata::Command &command)  {
        Queue &Q = *(this->queue);
        using namespace cmddata;
        switch(command.getCommandCode()) {
            case PUSH: 
                Q.push(command.getArg());
                break;
            case POP:
                std::cout << Q.pop() << '\n';
                break;
            case SIZE:
                std::cout << Q.getSize() << '\n';
                break;
            case EMPTY:
                std::cout << Q.empty() << '\n';
                break;
            case FRONT:
                std::cout << Q.front() << '\n';
                break;
            case BACK:
                std::cout << Q.back() << '\n';
                break;
        }
        return;
    }
};

int main(void)  {
    int N; std::cin >> N; std::cin.ignore();
    Handler H;
    for (std::size_t i = 0; i < N; ++i) {
        std::string cmd_str;
        std::getline(std::cin, cmd_str);
        H.processCommand(cmddata::Command(cmd_str));
    }
    return 0;
}