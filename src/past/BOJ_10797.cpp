#include <iostream>
#include <vector>

int main(void) {
    int day;
    std::cin >> day;
    day %= 10;
    int illegal_count = 0;

    for (int i = 0; i < 5; i++) {
        int tcarnum;
        std::cin >> tcarnum;
        tcarnum %= 10;
        if (tcarnum == day) {
            illegal_count++;
        }
    }
    std::cout << illegal_count << std::endl;
    return 0;
}
