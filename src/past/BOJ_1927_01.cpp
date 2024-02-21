#include <iostream>
#include <vector>
#include <climits>

class Heap {
    // This is "Minimum" Heap
private:
    enum NodeName  { ROOT = 1 };
    std::size_t      size = 0;
    std::size_t      capacity;
    std::vector<int> arr;
public:
    Heap(std::size_t capacity): capacity(capacity), arr(capacity + 1, INT_MAX) {}
private:
    void swap(std::size_t idx1, std::size_t idx2) {
        int temp = this->arr[idx2];
        this->arr[idx2] = this->arr[idx1];
        this->arr[idx1] = temp;
        return;
    }
public:
    void push(int val) {
        std::size_t cidx = this->size + 1;
        this->arr[cidx] = val;
        
        std::size_t pidx = cidx / 2;
        while (cidx != 1 && this->arr[cidx] < this->arr[pidx]) {
            // CAUTION:: Short Circuit
            swap(cidx, pidx);
            cidx = pidx;
            pidx = cidx / 2;
        }
        
        this->size++;
        return;
    }
    void pop(void) {
        // Happy return while pop operation is unavailable
        if (this->size == 0) {
            std::cout << 0 << std::endl;
            return;
        }
        
        std::cout << this->arr[ROOT] << std::endl;
        // Change root node to last node
        this->arr[ROOT] = this->arr[this->size];
        this->arr[this->size] = INT_MAX;
        this->size--;
        
        std::size_t cidx  = ROOT; // Start in root node
        std::size_t lchidx = cidx * 2;
        std::size_t rchidx = lchidx + 1;
        while (true) {
            if        (lchidx <= this->size && this->arr[cidx] > this->arr[lchidx]) {
                swap(lchidx, cidx);
                cidx = lchidx;
                lchidx = cidx * 2;
                rchidx = lchidx + 1;
            } else if (rchidx <= this->size && this->arr[cidx] > this->arr[rchidx]) {
                swap(rchidx, cidx);
                cidx = rchidx;
                lchidx = cidx * 2;
                rchidx = lchidx + 1;
            } else break;
        }
        return;
    }
};

class Command {
private:
    std::vector<int> cmds;
    std::size_t      n_of_push = 0;
    std::size_t      n_of_pop  = 0;
public:
    Command(std::size_t n): cmds(n) {
        for (int &cmd: this->cmds) {
            std::cin >> cmd;
            if (cmd == 0) this->n_of_pop++;
        }
        this->n_of_push = n - this->n_of_pop;
        return;
    }
public:
    const std::vector<int> &getCommand(void) const {
        return this->cmds;
    }
    std::size_t getNOfPushCommands(void) const {
        return this->n_of_push;
    }
    std::size_t getNOfPopCommands(void) const {
        return this->n_of_pop;
    }
};

class Handler {
private:
    Heap    *heap;
    Command *commands;
public:
    Handler(std::size_t n_of_cmds)
    : commands(new Command(n_of_cmds)) {
        this->heap = new Heap(this->commands->getNOfPushCommands());
        return;
    }
    ~Handler(void) {
        delete this->heap;
        delete this->commands;
        return;
    }
public:
    void processCommand(void) {
        for (const auto &command: this->commands->getCommand()) {
            switch(command) {
                case 0:
                    this->heap->pop();
                    break;
                default:
                    const auto &value = command;
                    this->heap->push(value);
                    break;
            }
        }
        return;
    }
};

int main(void) {
    std::size_t n_of_cmd; std::cin >> n_of_cmd;
    Handler(n_of_cmd).processCommand();
    return 0;
}
