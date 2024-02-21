#include <iostream>
#include <vector>
#include <climits>

enum CommandName { POP=0 };

class Heap {
private:
    enum NodeName { ROOT=0 };
    bool             (*cmp)(std::size_t, std::size_t);
    std::size_t      size = 0;
    std::size_t      capacity;
    std::vector<int> vec;
public:
    Heap(std::size_t capacity, bool (*cmp)(std::size_t, std::size_t)): capacity(capacity), vec(capacity), cmp(cmp) {
    }
private:
    void swap(std::size_t idx1, std::size_t idx2) {
        int temp = this->vec[idx2];
        this->vec[idx2] = this->vec[idx1];
        this->vec[idx1] = temp;
        return;
    }
    std::size_t get_parent_idx(std::size_t child_idx) const {
        return (child_idx - 1) / 2;
    }
    std::size_t get_lchild_idx(std::size_t parent_idx) const {
        return 2 * parent_idx + 1;
    }
    std::size_t get_rchild_idx(std::size_t parent_idx) const {
        return this->get_lchild_idx(parent_idx) + 1;
    }
    bool heap_property(std::size_t parent_idx, std::size_t child_idx) const {
        return this->cmp(this->vec[parent_idx], this->vec[child_idx]);
    }
    bool in_bound(std::size_t idx) const {
        return 0 <= idx && idx <= this->size - 1;
    }
    void heap_up(std::size_t idx) {
        // For push
        std::size_t pidx = this->get_parent_idx(idx);
        if (idx != ROOT && this->in_bound(pidx) && this->heap_property(pidx, idx)) {
            this->swap(idx, pidx);
            this->heap_up(pidx);
        }
        return;
    }
    void heap_down(std::size_t idx) {
        // For pop
        std::size_t lchidx = this->get_lchild_idx(idx);
        std::size_t rchidx = this->get_rchild_idx(idx);
        std::size_t proidx = idx;
        
        if (this->in_bound(lchidx) && this->heap_property(lchidx, proidx))
            proidx = lchidx;
        if (this->in_bound(rchidx) && this->heap_property(rchidx, proidx))
            proidx = rchidx;
        if (proidx != idx) {
            this->swap(idx, proidx);
            this->heap_down(proidx);
        }
        return;
    }
public:
    bool empty(void) {
        return (this->size == 0 ? true : false);
    }
    void print(void) const {
        for (std::size_t i = 0; i < this->size; ++i) {
            std::cout << this->vec[i] << " ";
        }
        std::cout << std::endl;
    }
public:
    void push(int val) {
        // AKA Insert
        // Happy return if capacity full
        if (this->size == this->capacity) {
            std::cout << "Capacity full, can't push." << '\n';
            return;
        }
        std::size_t child_idx = (this->size == 0 ? ROOT : this->size);
        this->vec[child_idx] = val;
        this->size++;
        
        this->heap_down(ROOT);
        return;
    }
    void pop(void) {
        // AKA Extract
        if (this->empty()) {
            std::cout << 0 << '\n';
            std::cout << "Empty!!\n";
            return;
        }
        std::size_t last_idx = this->size - 1;
        std::cout << this->vec[ROOT] << '\n';
        this->vec[ROOT] = this->vec[last_idx];
        
        this->size--;
        last_idx = this->size - 1;
        
        std::size_t parent_idx = ROOT;
        this->heap_down(parent_idx);
        return;
    }
};

class Command {
private:
    std::size_t      n_of_push = 0;
    std::size_t      n_of_pop  = 0;
    std::vector<int> vec;
public:
    Command(std::size_t n_of_commands): vec(n_of_commands, 0) {
        for (auto &command: this->vec) {
            std::cin >> command;
            if (command == POP) this->n_of_pop++;
        }
        this->n_of_push = n_of_commands - this->n_of_pop;
        return;
    }
public:
    const std::vector<int> &getCommands(void) const {
        return this->vec;
    }
    std::size_t getNOfPushCommands(void) const {
        return this->n_of_push;
    }
};

class Handler {
private:
    Command *commands;
    Heap    *heap;
public:
    Handler(std::size_t n_of_commands, bool (*cmp)(std::size_t, std::size_t)) {
        this->commands = new Command(n_of_commands);
        this->heap     = new Heap(this->commands->getNOfPushCommands(), cmp);
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
            std::cout << "Current Heap State: ";
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
    const auto min_heap_property = [](std::size_t p, std::size_t c)->bool {
        return p <= c;
    };
    Handler(n_of_commands, min_heap_property).processCommand();
    return 0;
}
