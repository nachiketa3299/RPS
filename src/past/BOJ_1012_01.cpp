#include <iostream>
#include <vector>
#include <algorithm>

class BchGrid {
private:
    typedef std::pair<std::size_t, std::size_t> BchPos;
    std::size_t M, N, K;
    std::vector<BchPos> bch_poss;
    std::vector<std::vector<bool>> bch_2d_grid;
    std::vector<std::vector<std::size_t>> bch_alist;
public:
    BchGrid(std::size_t M, std::size_t N, std::size_t K)
    : M(M), N(N), K(K),
    bch_2d_grid(M, std::vector<bool>(N, false)),
    bch_alist(K) {
        this->make_bch_2d_grid();
        this->make_bch_alist();
        //this->print_adj_list();
        return;
    }
private: /* For making adjlist */
    void print_adj_list(void) const {
        for (const auto &node: this->bch_alist) {
            std::cout << &node - &this->bch_alist[0] << " | ";
            for (const auto &adj_node: node) {
                std::cout << adj_node << " ";
            }
            std::cout << '\n';
        }
        return;
    }
    void make_bch_2d_grid(void) {
        for (std::size_t k = 0; k < this->K; ++k) {
            std::size_t x, y; std::cin >> x >> y;
            this->bch_poss.push_back(BchPos(x, y));
            this->bch_2d_grid[x][y] = true;
        }
        return;
    }
    void make_bch_alist(void) {
        for (const auto &bch_pos: this->bch_poss) {
            const auto &cbch_idx = &bch_pos - &this->bch_poss[0];
            for (const auto &poss_idx: this->find_possible_adj_bchidxs(bch_pos)) {
                const auto &cbch_alist = this->bch_alist[cbch_idx];
                if (std::find(cbch_alist.begin(), cbch_alist.end(), poss_idx) == cbch_alist.end()) {
                    this->bch_alist[cbch_idx].push_back(poss_idx);
                    this->bch_alist[poss_idx].push_back(cbch_idx);
                }
            }
        }
        return;
    }
    std::vector<std::size_t> find_possible_adj_bchidxs(const BchPos &bch_pos) {
        std::vector<std::size_t> possible_bchs;
        const auto &x = bch_pos.first;
        const auto &y = bch_pos.second;
        for (const auto &i: { -1, 1 }) {
            if (this->is_in_bound(x + i, y) && this->bch_2d_grid[x + i][y] == true) {
                const auto it = std::find(this->bch_poss.begin(), this->bch_poss.end(), BchPos(x + i, y));
                possible_bchs.push_back(std::distance(this->bch_poss.begin(), it));
            }
            if (this->is_in_bound(x, y + i) && this->bch_2d_grid[x][y + i] == true) {
                const auto it = std::find(this->bch_poss.begin(), this->bch_poss.end(), BchPos(x, y + i));
                possible_bchs.push_back(std::distance(this->bch_poss.begin(), it));
            }
        }
        return possible_bchs;
    }
    bool is_in_bound(std::size_t xidx, std::size_t yidx) const {
        return this->is_in_width_bound(xidx) && this->is_in_height_bound(yidx);
    }
    bool is_in_width_bound(std::size_t idx) const {
        return 0 <= idx && idx < this->M;
    }
    bool is_in_height_bound(std::size_t idx) const {
        return 0 <= idx && idx < this->N;
    }
private: /* For searching graph(adj-list) */
    void dfs(std::size_t idx, std::vector<bool> &visited) const {
        visited[idx] = true;
        const auto &calist = this->bch_alist[idx];
        for (const auto &bchidx: calist) {
            if (visited[bchidx] == false) {
                this->dfs(bchidx, visited);
            }
        }
        return;
    }
public:
    std::size_t getMinimumWormCount(void) const {
        std::vector<bool> visited(this->bch_poss.size(), false);
        std::size_t worm_cnt = 0;
        for (std::size_t idx = 0; idx < visited.size(); ++idx) {
            if (visited[idx] == false) {
                worm_cnt++;
                this->dfs(idx, visited);
            }
        }
        return worm_cnt;
    }
};

int main(void) {
    // For Fast IO
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    
    std::size_t T; std::cin >> T;
    for (std::size_t t = 0; t < T; ++t) {
        // Input per-Testcase
        std::size_t M, N, K; std::cin >> M >> N >> K;
        BchGrid G(M, N, K); // Input batch Bch position in here.
        
        // Process
        std::cout << G.getMinimumWormCount() << '\n';
    }
    return 0;
}
