#include <iostream>
#include <vector>
#include <queue>

namespace OP {
    const int NULLOP = -1;
    const int NULLCAL = -1;
}

class OpTree {
private:
    struct Node {
        int value;
        int op1_idx;
        int op2_idx;
        int op3_idx;
    };
    int seed;
    std::vector<Node> pos_nodes;
public:
    OpTree (int s) : seed(s) {
        this->pos_nodes.resize(this->seed);
        for (int i = 0; i < this->seed; i++) {

            int& v = this->pos_nodes[i].value;
            int& o1i = this->pos_nodes[i].op1_idx;
            int& o2i = this->pos_nodes[i].op2_idx;
            int& o3i = this->pos_nodes[i].op3_idx;

            v = i + 1;
            if (v % 3 == 0) {
                o1i = (v / 3) - 1;
                if (v % 2 == 0) {
                    o2i = (v / 2) - 1;
                } else {
                    o2i = OP::NULLOP;
                }
            } else if (v % 2 == 0) {
                o1i = OP::NULLOP;
                o2i = (v / 2) - 1;
            } else {
                o1i = OP::NULLOP;
                o2i = OP::NULLOP;
            }
            o3i = (v - 1) - 1; // if i == 0 , o3i = OP::NULLOP
        }
        return;
    }
    void print (void) const {
        for (int i = 0; i < this->seed; i++) {
            std::cout << this->pos_nodes[seed - i - 1].value << " (";
            std::cout << this->pos_nodes[seed - i - 1].op1_idx << ", ";
            std::cout << this->pos_nodes[seed - i - 1].op2_idx << ", ";
            std::cout << this->pos_nodes[seed - i - 1].op3_idx << ")";
            std::cout << std::endl;
        }
    }
    int getMinimumDepth (void) {
        int start_index = this->seed - 1;
        std::vector<int> distance(this->seed, OP::NULLCAL);
        distance[start_index] = 0;
        std::queue<int> q;
        q.push(start_index);
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            for (auto it: this->pos_nodes[curr]) {

            }
                
        }
        return -1;
    }
};


int main(void) {
    int N;
    std::cin >> N; // (1<= N <= 10^6)
    OpTree t(N);
    std::cout << t.getMinimumDepth() << std::endl;
    return 0;
}
