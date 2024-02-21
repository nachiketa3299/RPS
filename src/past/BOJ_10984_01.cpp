#include <iostream>

int main(void) {
    int T; std::cin >> T;
    for (int i = 0; i < T; ++i) {
        int N; std::cin >> N;

        int totalC = 0; double GPA = 0.0;

        for (int j = 0; j < N; ++j) {
            int C; double G; std::cin >> C >> G;
            totalC += C; GPA += C * G;
        }
        GPA /= totalC;
        std::cout << totalC << " " << GPA << '\n';
    }
    return 0;
}
