#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

const int CHSIZE = 8;

namespace BWCHAR {
    const char B = 'B';
    const char W = 'W';
}

namespace BWBOOL {
    const bool B = true;
    const bool W = false;
}

class Board {
private:
    std::vector<std::vector<bool>> b;
public:
    Board(int N, int M): b(N, std::vector<bool>(M, BWBOOL::W)) {
        this->getColumn();
        return;
    }
private:
    void getColumn(void) {
        for (std::size_t i = 0; i < this->b.size(); ++i) {
            std::string cc; std::getline(std::cin, cc);
            for (std::size_t j = 0; j < this->b[i].size(); ++j) {
                if (cc[j] == BWCHAR::B) { this->b[i][j] = BWBOOL::B; }
            }
        }
        return;
    }
public:
    void print(void) const {
        for (const auto &c: this->b) {
            for (const auto &r: c) {
                std::cout << (r ? BWCHAR::B : BWCHAR::W);
            }
            std::cout << '\n';
        }
        return;
    }

    int getMinimumChessModifyCount(const int chs) const {
        std::vector<int> counts;
        for (std::size_t n = 0; n + chs <= this->b.size(); ++n) {
            for (std::size_t m = 0; m + chs <= this->b[n].size(); ++m) {
                // Type 1 Chess Board
                int t1_cnt = 0;
                for (std::size_t i = 0; i < chs; ++i) {
                    for (std::size_t j = 0; j < chs; ++j) {
                        bool cs = this->b[n + i][m + j];
                        if (i % 2 == 0) {
                            if (j % 2 == 0) {
                                if (cs != BWBOOL::B) t1_cnt++;
                            } else {
                                if (cs != BWBOOL::W) t1_cnt++;
                            }
                        } else {
                            if (j % 2 == 0) {
                                if (cs != BWBOOL::W) t1_cnt++;
                            } else {
                                if (cs != BWBOOL::B) t1_cnt++;
                            }
                        }
                    }
                }
                counts.push_back(t1_cnt);
                // Type 2 Chess Board
                int t2_cnt = 0;
                for (std::size_t i = 0; i < chs; ++i) {
                    for (std::size_t j = 0; j < chs; ++j) {
                        bool cs = this->b[n + i][m + j];
                        if (i % 2 == 0) {
                            if (j % 2 == 0) {
                                if (cs != BWBOOL::W) t2_cnt++;
                            } else {
                                if (cs != BWBOOL::B) t2_cnt++;
                            }
                        } else {
                            if (j % 2 == 0) {
                                if (cs != BWBOOL::B) t2_cnt++;
                            } else {
                                if (cs != BWBOOL::W) t2_cnt++;
                            }
                        }
                    }
                }
                counts.push_back(t2_cnt);
            }
        }
        return *std::min_element(counts.begin(), counts.end());
    }
};

int main(void) {
    int N, M; std::cin >> N >> M; std::cin.ignore();
    Board B(N, M);
    std::cout << B.getMinimumChessModifyCount(CHSIZE) << '\n';
    return 0;
}
