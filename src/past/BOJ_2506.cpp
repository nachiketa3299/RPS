#include <iostream>
#include <vector>

int getScore(const std::vector<bool> c) {
    std::vector<int> tidxs;
    for (int i = 0; i < c.size(); i++) {
        if (c[i]) tidxs.push_back(i);
    }
    // 아무 것도 못 맞췄을 때
    if (tidxs.size() == 0) return 0;
    if (tidxs.size() == 1) return 1;

    int tscore = 1;
    
    int streak = 0;
    for (int i = 1; i < tidxs.size(); i++) {
        int cscore = 1;
        if (tidxs[i - 1] + 1 == tidxs[i]) {
            streak++;
        } else {
            streak = 0;
        }
        tscore += cscore + streak;
    }
    return tscore;
}

int main(void) {
    int N;
    std::cin >> N;
    std::vector<bool> c(N, false);
    for (int i = 0; i < N; i++) {
        int in;
        std::cin >> in;
        c[i] = (in == 1) ? true : false;
    }
    std::cout << getScore(c) << std::endl;
    return 0;
}
