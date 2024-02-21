#include <iostream>
#include <string>

namespace CODE {
    enum CMD { PUSH, POP, SIZE, EMPTY, TOP };
}

namespace STR {
    const std::string PUSH = "push";
    const std::string POP = "pop";
    const std::string SIZE = "size";
    const std::string TOP = "top";
    const std::string EMPTY = "empty";
}

class Command {
private:
    CODE::CMD cmd;
    int arg;
public:
    Command(const std::string &cmd_str) {
        int parse_idx = cmd_str.find(' ');
        if (parse_idx == std::string::npos) {
            // If `cmd_str` has no blank, it means it does not have any args.
            if (cmd_str == STR::TOP)
                this->cmd = CODE::CMD::TOP;
            else if (cmd_str == STR::SIZE)
                this->cmd = CODE::CMD::SIZE;
            else if (cmd_str == STR::EMPTY)
                this->cmd = CODE::CMD::EMPTY;
            else if (cmd_str == STR::TOP)
                this->cmd = CODE::CMD::TOP;
            else if (cmd_str == STR::POP)
                this->cmd = CODE::CMD::POP;
        } else {
            this->cmd = CODE::CMD::PUSH;
            this->arg = std::stoi(cmd_str.substr(parse_idx));
        }
        return;
    }
    CODE::CMD getCode(void) const { return this->cmd; }
    int getArg(void) const { return  this->arg; }
    void print(void) const { std::cout << this->cmd << " " << this->arg; };
};

class Stack {
private:
    enum ERRORCODE { STACK_IS_EMPTY=-1 };
    struct Node { 
        int value; 
        Node *next, *prev;
        Node(int value=0): value(value), next(nullptr), prev(nullptr) {}
    };
    Node *sn; // Sentinel Node for Stack
    std::size_t size;
private:
public:
    Stack(void): sn(new Node()), size(0) {
        this->sn->next = this->sn; 
        this->sn->prev = this->sn;
        return;
    }
    ~Stack(void) { 
        delete sn; 
        return;
    }

    void push(int value) {
        ++this->size;
        Node &sent = *(this->sn);
        Node *new_node = new Node(value);
        Node &head = *(this->sn->next);
        new_node->prev = &sent;
        new_node->next = &head;
        sent.next = new_node;
        head.prev = new_node;
        return;
    }

    int pop(void) {
        if (!(this->empty())) {
            --this->size;
            Node &sent = *(this->sn);
            Node &pop_target = *(this->sn->next);
            Node &head_next = *(this->sn->next->next);
            int pop_val = pop_target.value;
            sent.next = &head_next;
            head_next.prev = &sent;
            delete &pop_target;
            return pop_val;
        } else return STACK_IS_EMPTY;
    }

    int top(void) const {
        if (!(this->empty())) return this->sn->next->value;
        else return STACK_IS_EMPTY;
    }

    bool empty(void) const { 
        return (this->size == 0 ? true : false); 
    }

    std::size_t getSize(void) const { return this->size; }
};

class Handler {
private:
    Stack *stack;
public:
    Handler(void): stack(new Stack()) {}
    void processCommand(const Command &command) {
        using namespace CODE;
        switch(command.getCode()) {
            case PUSH:
                this->stack->push(command.getArg()); break;
            case POP:
                std::cout << this->stack->pop() << '\n'; 
                break;
            case SIZE:
                std::cout << this->stack->getSize() << '\n'; 
                break;
            case TOP:
                std::cout << this->stack->top() << '\n'; 
                break;
            case EMPTY:
                std::cout << this->stack->empty() << '\n'; 
                break;
        }
        return;
    }
};

int main(void) {
    int N; std::cin >> N; std::cin.ignore();
    Handler H;
    for (std::size_t i = 0; i < N; ++i) {
        std::string cmd_str; std::getline(std::cin, cmd_str);
        H.processCommand(Command(cmd_str));
    }
}