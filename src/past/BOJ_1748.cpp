#include <iostream>
#include <cmath>

class NewNumber {
private:
    std::size_t gen_num;
    std::size_t total_digit;
public:
    NewNumber(std::size_t N): gen_num(N) {
        this->cal_total_digit();
        return;
    }
    std::size_t getTotalDigit(void) const {
        return this->total_digit;
    }
private:
    void cal_total_digit(void) {
        std::size_t i_n_d = this->get_total_digit(this->gen_num);
        std::size_t total_digit = 0;
        for (std::size_t cd = 1; cd < i_n_d; ++cd)
            total_digit += cd * int(pow(10, cd) - pow(10, cd - 1));
        total_digit += i_n_d * (this->gen_num - int(pow(10, i_n_d - 1)) + 1);
        this->total_digit = total_digit;
        return;
    }
    std::size_t get_total_digit(std::size_t n) {
        std::size_t digit = 0;
        while(n != 0) { n /= 10; digit++; }
        return digit;
    }
};

int main(void) {
    std::size_t N; std::cin >> N;
    std::cout << NewNumber(N).getTotalDigit() << '\n';
    return 0;
}
