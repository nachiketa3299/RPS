#include <iostream>
#include <vector>

int getRemainApples(const std::vector<int>& s, const std::vector<int>& a) {
    int remain_apples = 0;
    for (int i = 0; i < s.size(); i++) {
        remain_apples += a[i] % s[i];
    }
    return remain_apples;
}

int main(void) {
    int N;
    std::cin >> N;
    std::vector<int> s(N, 0);
    std::vector<int> a(N, 0);

    for (int i = 0; i < N; i++) {
        std::cin >> s[i] >> a[i];
    }
    std::cout << getRemainApples(s, a) << std::endl;
    return 0;
}
