#include <iostream>

int main(void) {
    int total_price;
    std::cin >> total_price;

    int nine_price = 0;
    for (int i = 0; i < 9; i++) {
        int book_price;
        std::cin >> book_price;
        nine_price += book_price;
    }
    std::cout << total_price - nine_price << std::endl;
    return 0;
}
