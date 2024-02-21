#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    
    std::size_t N, M; std::cin >> N >> M;
    std::unordered_map<std::string, bool> map(N);
    
    for (std::size_t i = 0; i < N; ++i) {
        std::string name_hear; std::cin >> name_hear;
        map[name_hear] = true;
    }
    
    std::size_t cnt = 0;
    std::vector<std::string> see_and_hear;
    for (std::size_t i = 0; i < M; ++i) {
        std::string name_see; std::cin >> name_see;
        if (map[name_see]) {
            cnt++;
            see_and_hear.push_back(name_see);
        }
    }
    
    std::cout << cnt << std::endl;
    std::sort(see_and_hear.begin(), see_and_hear.end());
    for (const auto &e: see_and_hear)
        std::cout << e << '\n';
    
    
    return 0;
}
