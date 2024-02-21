#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
 
int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    std::size_t N, M; std::cin >> N >> M;
    std::unordered_map<std::string, std::string> site_dict;
    std::vector<std::string>                     query(M);

    // Make hash table of Site-Password
    for (std::size_t i = 0; i < N; ++i) {
        std::string s; std::cin >> s;
        std::string p; std::cin >> p;
        site_dict[s] = p;
    }

    // Make query vector of Site
    for (std::size_t i = 0; i < M; ++i)
        std::cin >> query[i];

    // Process
    for (const std::string &q: query)
        std::cout << site_dict[q] << '\n';

    return 0;
}
