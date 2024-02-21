#include <iostream>
#include <vector>

enum Sign { MIN=-1, ZER=0, PLU=1, DIF=2 };

typedef std::vector<std::vector<int>> TdVec;
struct PaperInfo {
    std::size_t i, j;
    std::size_t n;
    PaperInfo(std::size_t i, std::size_t j, std::size_t n): i(i), j(j), n(n) {}
    PaperInfo(void) {}
    std::vector<PaperInfo> slicePaper(void) const {
        if (this->n < 3) std::cout << "ERROR" << std::endl;
        std::vector<PaperInfo> rvec;
        std::size_t nn = this->n / 3;
        for (std::size_t i = 0; i < this->n; i+=nn) {
            for (std::size_t j = 0; j < this->n; j+=nn) {
                rvec.push_back(PaperInfo{ this->i + i, this->j + j, nn });
            }
        }
        return rvec;
    }
    void print(void) const {
        std::cout << "Pinfo Index: " << this->i << ", " << this->j << std::endl;
        std::cout << "Pinfo Size: " << this->n << std::endl;
        return;
    }
};

Sign verify(const PaperInfo &pinfo, const TdVec &p) {
    int init_val = p[pinfo.i][pinfo.j];
    for (std::size_t i = pinfo.i; i - pinfo.i < pinfo.n; ++i)
        for (std::size_t j = pinfo.j; j - pinfo.j < pinfo.n; ++j)
            if (p[i][j] != init_val) return Sign::DIF;
    return Sign(init_val);
}


void slice(const PaperInfo &pinfo, const TdVec &p, std::vector<int> &result) {
    Sign vresult = verify(pinfo, p);
    switch(vresult) {
        case Sign::DIF:
            for (const auto &npinfo: pinfo.slicePaper())
                slice(npinfo, p, result);
            break;
        default:
            result[vresult + 1]++;
            break;
    }
    return;
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    
    // Input
    std::size_t N; std::cin >> N;
    TdVec vec(N, std::vector<int>(N));
    for (std::size_t i = 0; i < N; ++i)
        for (std::size_t j = 0; j < N; ++j)
            std::cin >> vec[i][j];
    
    std::vector<int> result(3, 0);
    slice(PaperInfo{ 0, 0, N }, vec, result);
    for (const auto& r: result) std::cout << r << '\n';
    
    return 0;
}
