#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

class OpGraph {
private:
    struct Edge {
        std::size_t head, tail;
        Edge(std::size_t head, std::size_t tail): head(head), tail(tail) {}
    };
    enum { INF_DIST=-1 };
private:
    std::size_t N;
    std::vector<std::vector<std::size_t>> adj;
public:
    OpGraph(int N): N(N), adj(N + 1) {
        // Possible Vertices Size are N
        // Make Adjacent List with this
        // adj[0] is not used. 
        // Only adj[1] ~ adj[N] used.

        this->makeAdjList();
    }
private:
    void makeAdjList(void) {
        // Op 1 Connect
        for (std::size_t i = 1; i + 1 <= this->N; ++i)
            this->addEdge(Edge(i, 1 + i));
        // Op 2 Connect
        for (std::size_t i = 1; 2 * i <= this->N; ++i)
            this->addEdge(Edge(i, 2 * i));
        // Op 3 Connect
        for (std::size_t i = 1; 3 * i <= this->N; ++i)
            this->addEdge(Edge(i, 3 * i));
    }

    void addEdge(const Edge &e) {
        std::vector<std::size_t> &cadj = this->adj[e.head];

        auto fit = std::find(cadj.begin(), cadj.end(), e.tail);
        if (fit == cadj.end()) {
            this->adj[e.head].push_back(e.tail);
            this->adj[e.tail].push_back(e.head);
        }
        return;
    }

    void graphPrint(void) const;

    std::size_t BFS_getShortestPath(std::size_t sidx, std::size_t didx) const {
        std::vector<std::size_t> sh_path;
        std::vector<bool> visited(this->N+1, false);
        std::queue<std::size_t> Q;
        std::vector<int> distance(this->N+1, INF_DIST);

        Q.push(sidx); visited[sidx] = true; distance[sidx] = 0;
        std::size_t cidx = sidx;

        while (!Q.empty() && cidx != didx) {
            cidx = Q.front(); Q.pop();
            const auto &cadj = this->adj[cidx];
            for (const auto &v: cadj) {
                if (!visited[v]) {
                    visited[v] = true;
                    distance[v] = distance[cidx] + 1;
                    Q.push(v);
                }
            }
        }

        return distance[this->N];
    }

public:
    std::size_t getOptimizedOperationPathSize(void) const {
        return this->BFS_getShortestPath(1, this->N);
    }
};

int main(void) {
    std::size_t N; std::cin >> N;
    OpGraph G(N);
    std::cout << G.getOptimizedOperationPathSize() << std::endl;
    return 0;
}

void OpGraph::graphPrint(void) const {
    for (std::size_t v = 1; v <= this->N; ++v) {
        std::cout << v << " | ";
        for (const auto &e: this->adj[v])
            std::cout << e << " ";
        std::cout << '\n';
    }
    return;
}