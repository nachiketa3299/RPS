#include <iostream>
#include <algorithm>
#include <vector>

int main(void) {
    int N; std::cin >> N;
    std::vector<std::string> w_v;
    for (std::size_t i = 0; i < N; ++i) {
        std::string istr; std::cin >> istr;
        bool isFound = (std::find(w_v.begin(), w_v.end(), istr) != w_v.end());
        if (!isFound)
            w_v.push_back(istr);
    }

    std::stable_sort(w_v.begin(), w_v.end(), 
        [&](const std::string &ref1, const std::string &ref2)->bool {
            if (ref1.size() != ref2.size()) {
                return ref1.size() < ref2.size();
            } 
            else { 
                return ref1 < ref2; 
            }
        }
    );
    for (const std::string &w: w_v) std::cout << w << '\n';
    return 0;
}

