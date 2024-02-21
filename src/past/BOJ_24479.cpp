#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>

struct Edge {
    int tail, head;
    Edge(void):tail(0), head(0) {}
    Edge(int tail, int head): tail(tail), head(head) {}
    Edge(const Edge &e): tail(e.tail), head(e.head) {}
};


class Graph {
private:
    std::vector<std::list<int>> alist;
public:
    Graph(int nv, std::vector<struct Edge> edges): alist(nv) {
        for (const auto &edge: edges) {
            this->alist[edge.tail].push_back(edge.head);
            this->alist[edge.head].push_back(edge.tail);
        }
        for (auto &al: this->alist) al.sort();
        return;
    }
public:
    std::stack<int> DFSr(int sidx=1) const {
        std::stack<int> s;
        std::vector<bool> visited(this->alist.size(), false);
        s.push(sidx); visited[sidx] = true;
        this->DFS_recursive(s, visited);
        return s;
    }
private:
    void DFS_recursive(std::stack<int> &s, std::vector<bool> &visited) const {
        int cidx = s.top();
        for (auto it = this->alist[cidx].begin(); it != this->alist[cidx].end(); ++it) {
            if (visited[*it] == false) {
                visited[*it] = true;
                s.push(*it);
                this->DFS_recursive(s, visited);
            }
        }
        return;
    }
public:
    void print(void) const {
        for (const auto &al: this->alist) {
            std::cout << &al - &this->alist[0] << " | ";
            for (auto it = al.begin(); it != al.end(); ++it) std::cout << *it << " ";
            std::cout << "\n";
        }
        return;
    }
};

int main(void) {
    int nv; std::cin >> nv;
    int ne; std::cin >> ne;
    int sidx; std::cin >> sidx;
    std::vector<struct Edge> edges(ne);
    for(int i = 0; i < edges.size(); ++i) {
        int tt, th;
        std::cin >> tt >> th;
        edges[i] = Edge(tt - 1, th - 1);
    }
    Graph g(nv, edges);
    std::stack<int> visit_order = g.DFSr(sidx - 1);
    std::vector<int> result_order(nv, 0);
    for (int r = visit_order.size(); visit_order.empty() == false; --r, visit_order.pop())
        result_order[visit_order.top()] = r;
    for (const auto &r: result_order) std::cout << r << '\n';
    return 0;
}
