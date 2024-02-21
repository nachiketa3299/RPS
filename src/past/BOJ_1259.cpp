#include <iostream>
#include <cmath>

class IndexInteger {
private:
    int val;
    int t_digit;

    int calTotalDigit(void) const {
        int digit = 0; int n = this->val;
        while (n != 0) { n /= 10; digit++; }
        return digit;
    }

public:
    IndexInteger(int val): val(val), t_digit(this->calTotalDigit()) {}
    ~IndexInteger(void) {}

    int operator[] (const std::size_t idx) const {
        return this->val/int(pow(10,idx)) - (this->val/int(pow(10,idx+1)))*10;
    }
    int getTotalDigit(void) const { return this->t_digit; }
};

class PalindromeMachine {
private:
    IndexInteger *target;
public:
    PalindromeMachine(IndexInteger *target): target(target) {}
    ~PalindromeMachine(void) { delete this->target; return; }
    bool isPalindrome(std::size_t sidx=0) const {
        return this->r_p(sidx);
    }

    bool r_p(std::size_t idx) const {
        std::size_t e_idx = (*(this->target)).getTotalDigit() - idx - 1;
        if (idx >= e_idx) return true;
        else if ((*(this->target))[idx] == (*(this->target))[e_idx]) 
            return this->r_p(++idx);
        else return false;
    }
};

int main(void) {
    while (true) {
        int input; std::cin >> input;
        if (input == 0) break;
        else {
            PalindromeMachine PM(new IndexInteger(input));
            std::cout << (PM.isPalindrome() ? "yes" : "no") << '\n';
        }
    }
    return 0;
}
