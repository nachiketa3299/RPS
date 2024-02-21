#include <iostream>
#include <string>

void printStar(int n, const std::string starchar) {
    for (int i = 0; i < n; i++) {
        int init_space_count = n - i - 1;
        for (int s = 0; s < init_space_count; s++) {
            std::cout << " ";
        }

        for (int k = 0; k < 2 * i + 1; k++) {
            std::string to_print;
            if (k % 2 == 0) {
                to_print = starchar;
            } else {
                to_print = " ";
            }
            std::cout << to_print;
        }
        std::cout << std::endl;
    }
    return;
}

int main(void) {
    int N;
    std::cin >> N;
    const std::string starchar = "*";
    printStar(N, starchar);
    return 0;
}
