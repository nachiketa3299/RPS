#include <iostream>

int main(void) {
    const int GN = 5;
    int total_score = 0;
    for (int i = 0; i < GN; i++) {
        int t_score;
        std::cin >> t_score;
        total_score += t_score;
    }
    std::cout << total_score << std::endl;
    return 0;
}
