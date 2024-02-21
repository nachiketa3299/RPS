#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class Heap {
private:
    std::vector<int> vec;
    bool (*cmp)(int, int);
public:
    Heap(bool (*cmp)(int, int)): cmp(cmp) {
        std::make_heap(this->vec.begin(), this->vec.end(), this->cmp);
        return;
    }
public:
    void push(int val) {
        this->vec.push_back(val);
        std::push_heap(vec.begin(), vec.end(), this->cmp);
        return;
    }
    void pop() {
        if (this->vec.size() == 0) {
            std::cout << 0 << '\n';
            return;
        }
        
        std::cout << this->vec.front() << '\n';
        std::pop_heap(this->vec.begin(), this->vec.end(), this->cmp);
        this->vec.pop_back();
        
        return;
    }
};

class Command {
private:
    std::vector<int> vec;
public:
    Command(std::size_t n_of_commands): vec(n_of_commands) {
        for (auto &command: this->vec) std::cin >> command;
        return;
    }
public:
    const std::vector<int> &getCommands(void) const {
        return this->vec;
    }
};

class Handler {
private:
    enum CommandName { POP=0 };
    Heap    *heap;
    Command *commands;
public:
    Handler(std::size_t n_of_commands, bool (*cmp)(int, int))
    : commands(new Command(n_of_commands)), heap(new Heap(cmp)) {
        return;
    }
    ~Handler(void) {
        delete this->heap;
        delete this->commands;
        return;
    }
public:
    void processCommands(void) {
        for (const auto &command: this->commands->getCommands()) {
            switch(command) {
                case POP:
                    this->heap->pop();
                    break;
                default:
                    const int &value = command;
                    this->heap->push(value);
                    break;
            }
        }
        return;
    }
};

int main(void) {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
    std::size_t n_of_commands; std::cin >> n_of_commands;
    const auto cmp = [](int x, int y)->bool{
        if (abs(x) == abs(y)) return x > y;
        return abs(x) > abs(y);
    };
    Handler(n_of_commands, cmp).processCommands();
    return 0;
}
