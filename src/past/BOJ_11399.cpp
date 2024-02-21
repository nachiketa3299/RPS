#include <iostream>
#include <algorithm>
#include <vector>

std::size_t cumulativeSum(const std::vector<std::size_t> &m_p) {

    std::vector<std::size_t> cum_vec(m_p.size(), 0); // cumultative vector
    cum_vec[0] = m_p[0];

    for (std::size_t i = 1; i < m_p.size(); ++i)
        cum_vec[i] = cum_vec[i - 1] + m_p[i];

    std::size_t sum = 0;
    for (const std::size_t &c: cum_vec) 
        sum += c;

    return sum;
}

int main(void) {
    int N; std::cin >> N;
    std::vector<std::size_t> m_p(N); // minutes per person vector

    for (std::size_t i = 0; i < N; ++i)
        std::cin >> m_p[i];
    
    // Permutation? Combination?

    // if m_p = { 1, 2, 3, 4, 5 }
    // 1 + (1 + 2) + (1 + 2 + 3) + (1 + 2 + 3 + 4) + (1 + 2 + 3 + 4 + 5)
    // least index added most
    // so, sort m_p ascending

    std::sort(m_p.begin(), m_p.end());
    std::cout << cumulativeSum(m_p) <<  std::endl;

    return 0;
}