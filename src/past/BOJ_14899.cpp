#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <limits>
#include <algorithm>

class SynergeTable {
private:
    std::vector<std::vector<int>> vs;
public:
    SynergeTable(int N): vs(N, std::vector<int>(N, 0)) {}
public:
    int getSynerge(int idx1, int idx2) const { return this->vs[idx1][idx2] + this->vs[idx2][idx1]; }
    std::vector<std::vector<int>> getAdjacentList(void) const {
        std::vector<std::vector<int>> adj(this->vs.size());
        for (int i = 0; i < adj.size(); ++i) {
            for (int j = 0; j < adj.size(); ++j) {
                if (i != j) { adj[i].push_back(j); adj[j].push_back(i); } 
            }
        }
        return adj;
    }
public: /* input */
    friend std::istream& operator>>(std::istream& is, SynergeTable& ref) {
        for (std::vector<int>& v: ref.vs)
            for (int &s: v) is >> s;
        return is;
    }
};

class TeamMaker {
private:
    int size_pt; SynergeTable st;
public:
    TeamMaker(int N, SynergeTable ST): size_pt(N / 2),  st(ST) {}
public:
    int getOptStatGap(void) const {
        const std::vector<std::vector<int>> salist = this->st.getAdjacentList();
        std::vector<bool> visited(this->size_pt * 2, false); visited[0] = true;
        std::stack<int> s; s.push(0);
        int stat_gap = INT_MAX;
        while (s.empty() == false) {
            int cidx = s.top();
            const std::vector<int> &csalist = salist[s.top()];
            std::vector<int>::const_iterator nvidx_it = std::find_if(calist.begin(), calist.end(), [&visited](int idx)->bool{ return !visited[idx]; });
            if (s.size() < this->size_pt) {
                if (nvidx_it != calist.end()) {
                    int nvidx = *nvidx_it; s.push(nvidx); visited[nvidx] = true;
                } else {
                }
            } else {
                std::vector<bool> team(this->size_pt * 2, false); std::stack<int> s_copy = s;
                while(!s_copy.empty()) { team[s_copy.top()] = true; s_copy.pop(); }
                int cstat_gap = this->getStatGap(team);
                stat_gap = (cstat_gap > stat_gap) ? stat_gap : cstat_gap;
            }
            visited[s.top()] = false; s.pop();
        }
        return stat_gap;
    }
};

int main(void) {
    int N; std::cin >> N; // N is even number
    SynergeTable ST(N); std::cin >> ST;
    TeamMaker TM(N, ST); std::cout << TM.getOptStatGap() << '\n';
}
