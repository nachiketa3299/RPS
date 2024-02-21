// https://www.acmicpc.net/source/49448246

#include <iostream>


void star (int i, int j) {
    if (i % 3 == 1 && j % 3 == 1) {
        std::cout << " ";
    }
    else if(i >= 3 && j >= 3) {
            star(i / 3, j / 3);
            return;
    }
    else {
        std::cout << "*";
    } 
}

int main(void) {
    int n; 
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
                star(i, j);
        }
        std::cout << "\n";
    }
    return 0;
}
