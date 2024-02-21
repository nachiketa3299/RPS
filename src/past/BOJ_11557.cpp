#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct SchoolData {
    std::size_t alcohol;
    std::string name;
    SchoolData(std::size_t a, std::string name)
        : alcohol(a), name(name) {}
    static bool cmp(const SchoolData &ref1, const SchoolData &ref2) {
        return ref1.alcohol < ref2.alcohol;
    }
};

int main(void) {
    int T; std::cin >> T;
    for (std::size_t i = 0; i < T; ++i) {
        int N; std::cin >> N; std::vector<SchoolData> s_v;
        for (std::size_t j = 0; j < N; ++j) {
            std::string name; std::size_t alcohol;
            std::cin >> name >> alcohol;
            s_v.emplace_back(alcohol, name);
        }
        std::vector<SchoolData>::iterator max_s = std::max_element(s_v.begin(), s_v.end(), SchoolData::cmp);
        std::cout << max_s->name << '\n';
    }
    return 0;
}
