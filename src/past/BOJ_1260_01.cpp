#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

enum SortOrder { ASC, DSC };

class Graph {
private:
    std::vector<std::vector<int>> adj_list;
public:
    Graph(int nv=0): adj_list(nv + 1) {}; 

    void addEdge(std::size_t head_idx, std::size_t tail_idx) {
        std::vector<int> &cvh_adj_list = this->adj_list[head_idx];
        std::vector<int> &cvt_adj_list = this->adj_list[tail_idx];

        auto fit = std::find(cvh_adj_list.begin(), cvh_adj_list.end(), tail_idx);
        if (fit == cvh_adj_list.end()) {
            cvh_adj_list.push_back(tail_idx);
            cvt_adj_list.push_back(head_idx);
        }
        return;
    }
    void sortEdges(SortOrder mod) {
        if (mod == ASC) {
            for (std::size_t i = 1; i < this->adj_list.size(); ++i) {
                std::vector<int> &cadj_list = this->adj_list[i];
                std::sort(cadj_list.begin(), cadj_list.end());
            }
        } else {
            for (std::size_t i = 1; i < this->adj_list.size(); ++i) {
                std::vector<int> &cadj_list = this->adj_list[i];
                std::sort(cadj_list.begin(), cadj_list.end(), [](const int& ref1, const int &ref2){ return ref1 > ref2; });
            }
        }
        return;
    }
    void print(void) const {
        for (std::size_t i = 1; i < this->adj_list.size(); ++i) {
            std::cout << i << " | ";
            for (std::size_t j = 0; j < this->adj_list[i].size(); ++j) {
                std::cout << this->adj_list[i][j] << " ";
            }
            std::cout << '\n';
        }
        return;
    }

    void printBFSResult(std::size_t sidx) const {
        std::queue<std::size_t> Q;
        std::vector<bool> visited(this->adj_list.size(), false);
        Q.push(sidx);

        for (std::size_t cidx = Q.front(); !Q.empty(); Q.pop()) {

            if (!visited[cidx]) {
                std::cout << cidx << " "; 
                visited[cidx] = true; 
            }

            const auto &cadj_list = this->adj_list[cidx];
            for (const int &v: cadj_list) 
                if (!visited[v]) 
                    Q.push(v);
            cidx = Q.front();
        }
        std::cout << '\n';
        return;
    }

    void printDFSResult(std::size_t sidx) const {
        std::stack<std::size_t> S;
        std::vector<bool> visited(this->adj_list.size(), false);
        S.push(sidx); 

        while (!S.empty()) {
            std::size_t cidx = S.top(); S.pop();
            if (!visited[cidx]) {
                std::cout << cidx << " ";
                visited[cidx] = true;
            }
            const auto &cadj_list = this->adj_list[cidx];
            for (const int &v: cadj_list) 
                if (!visited[v])
                    S.push(v);
        }
        std::cout << '\n';
        return;
    }
};

int main(void) {
    int N, M, V; std::cin >> N >> M >> V;
    // N: n of Vertices  M: n or Edges V: idx of DFS & VFS
    Graph G(N);

    for (std::size_t i = 0; i < M; ++i) {
        std::size_t t_head, t_tail; std::cin >> t_head >> t_tail;
        G.addEdge(t_head, t_tail);
    }
    G.sortEdges(DSC);
    G.printDFSResult(V);

    G.sortEdges(ASC);
    G.printBFSResult(V);
    return 0;
}