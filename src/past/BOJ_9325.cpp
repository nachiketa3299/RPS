#include <iostream>
struct Option {
    int n, p;
    Option(int n, int p) : n(n), p(p) {}
    int getTotal(void) { return this->n * this->p; };
};

int main(void) {
    int T;
    std::cin >> T;
    for (int i = 0; i < T; i++) {
        int total_price = 0;
        int s;
        std::cin >> s;
        total_price += s;
        int n;
        std::cin >> n;
        for (int j = 0; j < n; j++) {
            int on, op;
            std::cin >> on >> op;
            total_price += Option(on, op).getTotal();
        }
        std::cout << total_price << std::endl;
    }
    return 0;
}
