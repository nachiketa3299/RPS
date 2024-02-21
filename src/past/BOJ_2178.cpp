#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <climits>

class Graph {
private:
    std::vector<std::vector<std::size_t>> alist;
public:
    Graph(const std::vector<std::string> &vec): alist(vec.size() * vec[0].size()) {
        const auto get_bound_adj_idxs = [&](int i, int j) {
            std::vector<std::pair<int, int>> r;
            if (i - 1 >= 0)                 r.push_back({ i - 1, j     });
            if (i + 1 <= vec.size() - 1)    r.push_back({ i + 1, j     });
            if (j - 1 >= 0)                 r.push_back({ i    , j - 1 });
            if (j + 1 <= vec[0].size() - 1) r.push_back({ i    , j + 1 });
            return r;
        };
        const auto alist_idx = [&](std::size_t i, std::size_t j) {
            return vec[0].size() * i + j;
        };
        for (std::size_t i = 0; i < vec.size(); ++i) {
            for (std::size_t j = 0; j < vec[i].size(); ++j) {
                if (vec[i][j] == '1') {
                    for (const auto &bnd_idx: get_bound_adj_idxs(i, j)) {
                        const auto &bi = bnd_idx.first;
                        const auto &bj = bnd_idx.second;
                        if (vec[bi][bj] == '1') {
                            const auto hnidx = alist_idx(i, j);
                            const auto tnidx = alist_idx(bi, bj);
                            if (std::find(this->alist[hnidx].begin(), this->alist[hnidx].end(), tnidx) == this->alist[hnidx].end()) {
                                this->alist[hnidx].push_back(tnidx);
                                this->alist[tnidx].push_back(hnidx);
                            }
                        }
                    }
                }
            }
        }
        return;
    }
    int DFS(std::size_t sidx=0) const {
        std::vector<bool> visited(alist.size(), false);
        std::vector<int> distance(alist.size(), INT_MAX);
        std::queue<std::size_t> q;
        q.push(sidx); distance[sidx] = 1;
        this->dfs(visited, distance, q);
        return distance.back();
    }
    void dfs(std::vector<bool> &visited, std::vector<int> &distance, std::queue<std::size_t> &q) const {
        while (!q.empty()) {
            std::size_t cidx = q.front(); q.pop();
            if (cidx == this->alist.size() - 1) break;
            if (visited[cidx] != true) {
                visited[cidx] = true;
                for (const auto& aidx: this->alist[cidx]) {
                    if (visited[aidx] != true) {
                        q.push(aidx);
                        distance[aidx] = distance[cidx] + 1;
                        //std::cout << "Distance" << aidx << ": " << distance[aidx] << std::endl;
                    }
                }
            }
        }
        return;
    }
private:
    
public:
    void print_alist(void) const {
        for (const auto &calist: this->alist) {
            std::cout << &calist - &(this->alist[0]) << " | ";
            for (const auto &nidx: calist) std::cout << nidx << " ";
            std::cout << std::endl;
        }
        return;
    }
};

int main(void) {
    std::size_t N, M; std::cin >> N >> M;
    std::vector<std::string> vec(N);
    for (std::size_t i = 0; i < N; ++i)
        std::cin >> vec[i];
    Graph g(vec);
    std::cout << g.DFS() << std::endl;
    
    return 0;
}
