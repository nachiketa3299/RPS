#include <vector>
#include <iostream>
#include <climits>

// INT_MAX is the expression of "EMPTY"

enum Command { POP=0 };

class MinHeap {
private:
    enum HeapNodeName {ROOT=0};
    std::size_t size = 0;
    std::size_t capacity = 100'000;
    const std::vector<std::size_t> commands;
    std::vector<int> arr;
public:
    MinHeap(const std::vector<std::size_t> &commands): commands(commands), arr(capacity, INT_MAX) {}
public:
    void processCommands(void) {
        for (const auto &command: this->commands) {
            switch(command) {
                case POP:
                    this->pop();
                    break;
                default:
                    this->push(static_cast<int>(command));
                    break;
            }
        }
        return;
    }
private: /* Index-making privae methods */
    std::size_t get_rchild_idx(const std::size_t pidx) {
        return 2 * (pidx + 1);
    }
    std::size_t get_lchild_idx(const std::size_t pidx) {
        return 2 * (pidx + 1) - 1;
    }
    std::size_t get_parent_idx(const std::size_t cidx) {
        return ((cidx + 1) / 2) - 1;
    }
    void swap(const std::size_t idx1, const std::size_t idx2) {
        auto tval = this->arr[idx1];
        this->arr[idx1] = this->arr[idx2];
        this->arr[idx2] = tval;
        return;
    }
private: /* Real processing private methods */
    void push(const int val) {
        // Size up first
        (this->size)++;
        
        // Capacity Check!
        if (this->size > this->capacity) {
            (this->size)--;
            std::cout << "Capacity Max" << std::endl;
            return;
        }
        
        // push element at the leafeast node
        auto cidx = this->size - 1;
        this->arr[cidx] = val;
        
        // Bubble up till min-heap is meaningfull
        auto pidx = this->get_parent_idx(cidx);
        while (cidx != 0 && this->arr[cidx] < this->arr[pidx]) {
            this->swap(cidx, pidx);
            cidx = pidx;
            pidx = this->get_parent_idx(cidx);
        }
        return;
    }
        
    void pop(void) {
        // There's no element in heap, nothing to pop
        if (this->size == 0) {
            std::cout << 0 << std::endl;
            return;
        }
        
        // Print Root's value (minimum val in heap)
        std::cout << this->arr[ROOT] << std::endl;
        
        // Deletion
        auto last_idx = this->size - 1;
        this->arr[ROOT] = this->arr[last_idx];
        this->arr[last_idx] = INT_MAX;
        
        auto cidx = static_cast<std::size_t>(ROOT);
        while (true) {
        this->size--;
        return;
    }
};

int main(void) {
    // Input
    std::size_t N; std::cin >> N;
    std::vector<std::size_t> commands(N, 0);
    for (auto &command: commands) std::cin >> command;
    
    MinHeap m_heap(commands);
    m_heap.processCommands();
    return 0;
}
