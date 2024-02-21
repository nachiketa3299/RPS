#include <iostream>
#include <vector>

enum RGB { R=0, G=1, B=2 };

struct Selection {
    RGB         color = RGB::R;
    std::size_t price = 0;
    Selection(RGB color, std::size_t price):
    color(color), price(price) {}
    Selection(void) {}
};

std::size_t solution(std::size_t clev, const std::vector<std::vector<std::size_t>> &color_vecs, std::vector<Selection> &cache) {
    if (clev == 0) {
        
    }
    return 0;
}

int main(void) {
    std::size_t N; std::cin >> N;
    
    std::vector<std::vector<std::size_t>> color_vecs(N, std::vector<std::size_t>(3));
    for (auto &color_vec: color_vecs) {
        for (auto &color: color_vec) std::cin >> color;
    }
    
    std::vector<Selection> cache(N);
    
    std::cout << solution(0, color_vecs, cache) << std::endl;
    
    return 0;
}
