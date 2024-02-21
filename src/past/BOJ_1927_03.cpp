#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

enum CommandName { POP=0 };

class Heap {
private:
    std::vector<int> vec;
    bool (*cmp)(std::size_t, std::size_t);
    std::size_t size = 0;
public:
    Heap(bool (*cmp)(std::size_t, std::size_t)):
    cmp(cmp) {
        std::make_heap(this->vec.begin(), this->vec.end(), this->cmp);
    }
public:
    void push(int val) {
        this->vec.push_back(val);
        std::push_heap(this->vec.begin(), this->vec.end(), this->cmp);
        this->size++;
        return;
    }
    void pop(void) {
        if (this->size == 0) {
            std::cout << 0 << '\n';
            return;
        }
        std::cout << this->vec.front() << '\n';
        std::pop_heap(this->vec.begin(), this->vec.end(), this->cmp);
        this->vec.pop_back();
        this->size--;
        return;
    }
    void print(void) const {
        for (const auto& e: this->vec) {
            std::cout << e << " ";
            if (&e - &this->vec[0] == this->size - 1) std::cout << "| ";
        }
        std::cout << '\n';
        return;
    }
};

class Command {
private:
    std::vector<int> vec;
public:
    Command(std::size_t n_of_commands): vec(n_of_commands, 0) {
        for (auto &command: this->vec) {
            std::cin >> command;
        }
        return;
    }
public:
    const std::vector<int> &getCommands(void) const {
        return this->vec;
    }
};

class Handler {
private:
    Command *commands;
    Heap    *heap;
public:
    Handler(std::size_t n_of_commands, bool (*cmp)(std::size_t, std::size_t)) {
        this->commands = new Command(n_of_commands);
        this->heap     = new Heap(cmp);
        return;
    }
    ~Handler(void) {
        delete this->commands;
        delete this->heap;
        return;
    }
public:
    void processCommand(void) {
        for (const auto& command: this->commands->getCommands()) {
            switch (command) {
                case POP:
                    this->heap->pop();
                    break;
                default:
                    const auto &value = command;
                    this->heap->push(value);
                    break;
            }
            /*
            std::cout << "Cheap: ";
            this->heap->print();
             */
        }
        return;
    }
};

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    
    std::size_t n_of_commands; std::cin >> n_of_commands;
    const auto min_heap = [](std::size_t idx1, std::size_t idx2)->bool {
        return idx1 >= idx2;
    };
    Handler(n_of_commands, min_heap).processCommand();
    return 0;
}
