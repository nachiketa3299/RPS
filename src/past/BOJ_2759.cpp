#include <iostream>
#include <vector>
#include <algorithm>

std::size_t recur(std::size_t end_idx, const std::vector<std::size_t> &score_per_step, std::vector<std::size_t> &score_cache) {
    if (end_idx - 2 >= 0) {
        std::size_t cand1 = recur(end_idx - 3, score_per_step, score_cache) + score_per_step[end_idx - 1]                     + score_per_step[end_idx];
        std::size_t cand2 =                                                   recur(end_idx - 2, score_per_step, score_cache) + score_per_step[end_idx];
        score_cache[end_idx] = std::max({ cand1, cand2 });
        return score_cache.back();
    } else return score_per_step.front();
}

std::size_t calculate(const std::vector<std::size_t> &score_per_step, std::vector<std::size_t> &score_cache) {
    std::size_t end_step_idx = score_per_step.size() - 1;
    return recur(end_step_idx, score_per_step, score_cache);
}

int main(void) {
    // Input
    std::size_t n_of_steps; std::cin >> n_of_steps;
    std::vector<std::size_t> score_per_step(n_of_steps);
    for (auto &step: score_per_step) std::cin >> step;

    // Process
    std::vector<std::size_t> score_cache(n_of_steps, score_per_step[0]);

    std::size_t max_score = calculate(score_per_step, score_cache);
    // Output
    std::cout << max_score << std::endl;
    return 0;
}
