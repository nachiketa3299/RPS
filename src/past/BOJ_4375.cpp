#include <iostream>
#include <string>
#include <algorithm>

struct BigOneNumber {
    std::string str;
    BigOneNumber(std::size_t digit) {
        for (std::size_t d = 0; d < digit; ++d)
            this->str += "1";
        return;
    }
    BigOneNumber(std::string str): str(str) {}
    BigOneNumber(const BigOneNumber &ref): str(ref.str) {}
    int operator%(int val) {
        BigOneNumber tbo(*(this));
        while(tbo >= val) {
            tbo -= val;
            std::cout << "tob: " << tbo.str << " val: " << val << "\n";
        }
        //std::cout << "So the return value is: " << tbo.str << '\n';
        return std::stoi(tbo.str);
    }

    BigOneNumber &operator-=(int val) {
        (*this) = (*this) - val;
        return (*this);
    }

    BigOneNumber operator-(int val) {
        std::string val_str = std::to_string(val);
        std::string bo_str = this->str;
        std::reverse(val_str.begin(), val_str.end());
        std::reverse(bo_str.begin(), bo_str.end());
        int next_carry = 0;
        std::string result_str = "";

        for (std::size_t i = 0; i < val_str.size(); ++i) {
            int cur_bo_digit = bo_str[i] - '0';
            int cur_val_digit = val_str[i] - '0';
            int cur_result_digit = cur_bo_digit - cur_val_digit + next_carry;
            if (cur_result_digit < 0) {
                next_carry = -1;
                cur_result_digit += 10;
            } else next_carry = 0;

            result_str += std::to_string(cur_result_digit);
        }

        for (std::size_t i = val_str.size(); i < bo_str.size(); ++i) {
            int cur_bo_digit = bo_str[i] - '0';
            int cur_result_digit = cur_bo_digit + next_carry;

            if (cur_result_digit < 0) {
                next_carry = -1;
                cur_result_digit += 10;
            } else next_carry = 0;

            result_str += std::to_string(cur_result_digit);
        }
        std::reverse(result_str.begin(), result_str.end());
        if (*result_str.begin() == '0' && result_str.size() > 1) {
            std::size_t last_zero_idx = 0;
            for (std::size_t i = 1; i < result_str.size(); ++i) {
                if (result_str[i] == '0') last_zero_idx = i;
                else break;
            }
            result_str = result_str.substr(last_zero_idx + 1);
        }
        return BigOneNumber(result_str);
    }

    bool operator>=(int ref) {
        std::string ref_str = std::to_string(ref);
        //std::cout << "Comparing: " << this->str << " > " << ref_str << '\n';
        if (this->getSize() > ref_str.size()) return true;
        else if (this->getSize() < ref_str.size()) return false;
        else {
            for (std::size_t i = 0; i < this->getSize(); ++i) {
                int cur_bo_digit = this->str[i] - '0';
                int cur_re_digit = ref_str[i] - '0';
                if (cur_bo_digit > cur_re_digit) {
                    return true;
                } 
                else if (cur_bo_digit < cur_re_digit) {
                    return false;
                }
                else ;
            }
            //std::cout << "SAME\n";
            return true;
        }
    }


    std::size_t getSize(void) const { return this->str.size(); }
    BigOneNumber &operator++() { this->str += "1"; return (*this); }
};

int getSmallestDigit(const std::string &input) {
    std::size_t input_digit = input.size();
    int input_val = std::stoi(input);
    BigOneNumber on(input_digit);

    for(std::size_t d = input_digit; ; ++d) {
        if (on % input_val == 0) {
            //std::cout << "FUCK?\n";
            return on.getSize();
        } 
        else {
            //std::cout << "INCREASING\n";
            ++on; // increse DIGIT by 1 (ex. 11 -> 111)
        } 
    }
}

int main(void) {
    while(!std::cin.eof()) {
        std::string n; std::cin >> n;
        std::cout << getSmallestDigit(n) << '\n';
        std::cout << "IAMFUCKINGDOING\n";
    }
    return 0;
}
