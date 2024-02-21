#include <iostream>
#include <string>

void printStar (int n, const std::string starchar) {
    for (int i = 0; i < n; i++) {
        const std::string pixel = (i % 2 == 0) ? starchar + " " : " " + starchar;
        for (int j = 0; j < n; j++) {
            std::cout << pixel;
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
