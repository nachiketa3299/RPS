#include <iostream>
const int DIGNUM = 5;
int makeVnum(int * arr) {
    int vnum = 0;
    for (int i = 0; i < DIGNUM; i++) {
        vnum += arr[i] * arr[i];
    }
    return vnum % 10;
}

int main(void) {
    int dig_arr[DIGNUM];
    for (int i = 0; i < DIGNUM; i++) {
        std::cin >> dig_arr[i];
    }
    std::cout << makeVnum(dig_arr) << std::endl;
    return 0;
}
