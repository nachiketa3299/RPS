#include <iostream>
#include <vector>
#include <algorithm>

class Floors {
private:
    std::size_t N;
    std::vector<std::size_t> scores;
    std::vector<std::size_t> cache;
public:
    Floors(std::size_t N): N(N), scores(N) {
        this->flourish_score();
        this->flourish_cache();
        return;
    }
private:
    void flourish_score(void) {
        for (auto &score: scores) std::cin >> score;
        return;
    }
    void flourish_cache(void) {
        for (std::size_t i = 2; i < N; ++i) {
            std::size_t poss1 = this->cache[i - 1] + this->scores[i];
            std::size_t poss2 = this->cache[i - 2] + this->scores[i] + this->scores[i - 1];
            this->cache[i] = std::max(poss1, poss2);
        }
        return;
    }
public:
    std::size_t getMaxScore(void) const {
        return this->cache.back();
    }
};

int main(void) {
    // Input
    std::size_t N; std::cin >> N;
    std::cout << Floors(N).getMaxScore() << std::endl;

    return 0;
}
