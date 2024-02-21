#include <iostream>
#include <vector>
#include <string>

struct BigNumber {

    std::vector<int> bnv;
    std::string bnstr;

    BigNumber(void): bnstr(""), bnv(0) {}
    BigNumber(std::string bnstr): bnstr(bnstr), bnv(BigNumber::StoV(bnstr)) {}
    BigNumber(std::vector<int> bnv): bnstr(BigNumber::VtoS(bnv)), bnv(bnv) {}
    BigNumber(const struct BigNumber &b): bnstr(b.bnstr), bnv(b.bnv) {}

    static std::vector<int> StoV(std::string bnstr) {
        std::vector<int> bnv(bnstr.size());
        for(int i = 0; i < bnstr.size(); i++) {
            bnv[bnstr.size() - i - 1] = bnstr[i] - '0';
        }
        return bnv;
    }

    static std::string VtoS(std::vector<int> bnv) {
        std::string bnstr = "";
        for (int i = bnv.size() - 1; i >= 0; i--) {
            bnstr += bnv[i] + '0';
        }
        return bnstr;
    }

    int getSize(void) const {
        return this->bnstr.size();
    }
    int getDigitAt(int idx) const {
        return this->bnv[idx];
    }

    struct BigNumber operator+ (struct BigNumber& b2) {
        std::vector<int> nbnv;

        BigNumber* sn = (b2.getSize() >= this->getSize()) ? this : &b2;
        BigNumber* ln = (b2.getSize() < this->getSize()) ? this : &b2;

        int carry = 0;
        for (int i = 0; i < sn->getSize(); i++) {
            int sum = this->getDigitAt(i) + b2.getDigitAt(i) + carry;
            if (sum >= 10) {
                carry = 1;
                sum %= 10;
            } else {
                carry = 0;
            }
            nbnv.push_back(sum);
        }
        for (int i = sn->getSize(); i < ln->getSize(); i++) {
            int sum = carry + ln->getDigitAt(i);
            if (sum >= 10) {
                carry = 1;
                sum %= 10;
            } else {
                carry = 0;
            }
            nbnv.push_back(sum);
        }
        if (carry == 1) nbnv.push_back(carry);
        return BigNumber(nbnv);
    }

    std::string toStr(void) {
        this->bnstr = BigNumber::VtoS(this->bnv);
        return this->bnstr;
    }
    void print(void) {
        std::cout << this->toStr() << std::endl;
        return;
    }
};

struct BigNumber fib (int n) {
    if (n == 0) return BigNumber("0");
    else if (n == 1) return BigNumber("1");
    else {

        struct BigNumber a = BigNumber("0");
        struct BigNumber b = BigNumber("1");
        struct BigNumber c;

        for (int i = 2; i <= n; i++) {
            c = a + b;
            a = b;
            b = c;
        }

        return c;
    }
}

int main(void) {
    int n; std::cin >> n;
    struct BigNumber c(fib(n));
    fib(n).print();
    return 0;
}
