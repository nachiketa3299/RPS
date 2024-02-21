#include <iostream>

void inputScore(int &score) {
    std::cin >> score;
    if (score < 40) score = 40;
    return;
}

int main(void) {
    const std::size_t i_n = 5;
    int average = 0;
    for (std::size_t i = 0; i < i_n; ++i) {
        int p_score; inputScore(p_score);
        average += p_score;
    }
    std::cout << average / i_n << '\n';
    return 0;
}
