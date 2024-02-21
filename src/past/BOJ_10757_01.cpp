#include <iostream>
#include <string>
#include <algorithm>

struct BigNumber {
private:
    std::string str;
public:
    BigNumber(std::string str): str(str) {}

    friend std::ostream& operator<<(std::ostream& os, const struct BigNumber &ref) {
        os << ref.str; return os;
    }

    friend struct BigNumber operator+(const struct BigNumber &ref1, const struct BigNumber &ref2) {
        std::string ls = (ref1.str.size() >= ref2.str.size() ? ref1.str : ref2.str);
        std::string ss = (ref1.str == ls ? ref2.str : ref1.str);
        std::reverse(ss.begin(), ss.end()), std::reverse(ls.begin(), ls.end());

        std::string rs = ""; int carry = 0;

        for (std::size_t i = 0; i < ss.size(); ++i) {
            // char -> int && Add
            int cr = (ss[i] - '0') + (ls[i] - '0') + carry;
            // Manage Carry
            if (cr >= 10) { cr -= 10; carry = 1; } else carry = 0;
            // int -> char && push to result string
            rs += (cr + '0');
        }

        for (std::size_t i = ss.size(); i < ls.size(); ++i) {
            int cr = (ls[i] - '0') + carry;
            if (cr >= 10) { cr -= 10; carry = 1; } else carry = 0;
            rs += (cr + '0');
        }

        if (carry == 1) rs += "1";

        std::reverse(rs.begin(), rs.end());
        return { rs };
    }
};

int main(void) {
    std::string A, B; std::cin >> A >> B;
    std::cout << BigNumber(A) + BigNumber(B) << '\n';
    return 0;
}
