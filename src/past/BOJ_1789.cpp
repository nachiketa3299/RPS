#include <iostream>

int cal(unsigned long int S) {
    unsigned long int ni = 0;
    int r;
    
    for (int i = 1;;i++) {
        ni += i;
        if (ni > S) {
            r = i - 1; 
            break;
        } else if (ni == S) {
            r = i;
            break;
        }
    }
    return r;
}

int main(void) {
    unsigned long int S;
    std::cin >> S;
    std::cout << cal(S) << std::endl;
    return 0;
}
