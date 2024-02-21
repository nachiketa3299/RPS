#include <iostream>

int getGCF(int a, int b) {
    int r = a % b;
    if (r == 0)
        return b;
    return getGCF(b, r);
}

int getLCM(int a, int b) {
    return a * b / getGCF(a, b);
}


int main(void) {
    int a, b;
    std::cin >> a >> b;
    std::cout << getGCF(a, b) << std::endl;
    std::cout << getLCM(a, b) << std::endl;
    return 0;
}
