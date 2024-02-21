#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

typedef std::vector<std::string> Vstring;

Vstring intersect(const Vstring &nh_v, const Vstring &ns_v) {
    Vstring nhs_v;
    for (const std::string nh: nh_v) {
        if (std::find(ns_v.begin(), ns_v.end(), nh) != ns_v.end()) {
            nhs_v.push_back(nh);
        }
    }
    return nhs_v;
}

int main(void) {
    int N, M; std::cin >> N >> M;
    Vstring nh_v(N);
    Vstring ns_v(M);

    for (std::size_t i = 0; i < N; ++i)
        std::cin >> nh_v[i];
    for (std::size_t i = 0; i < M; ++i)
        std::cin >> ns_v[i];
    
    Vstring nhs_v = intersect(nh_v, ns_v);
    std::sort(nhs_v.begin(), nhs_v.end());
    std::cout << nhs_v.size() << std::endl;
    for (const std::string nhs: nhs_v) 
        std::cout << nhs << std::endl;

    return 0;
}