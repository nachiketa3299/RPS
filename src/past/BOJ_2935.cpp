#include <iostream>
#include <string>
enum Operator { ADD, MUL };

struct Base10 {
private:
    int n, n2 = 0;
    bool has_n2 = false;
public:
    Base10(void): n(0) {}
    Base10(int n): n(n) {}
    Base10(int n, int n2, bool has_n2): n(n), n2(n2), has_n2(has_n2) {}
    Base10(const std::string &nstr): n(nstr.size() - 1) {}
    Base10(const struct Base10 &ref): n(ref.n) {}

    friend struct Base10 operator+(const struct Base10 &ref1, const struct Base10 &ref2) {
        int ln = (ref1.n >= ref2.n ? ref1.n : ref2.n);
        int sn = (ln == ref1.n ? ref2.n : ref1.n);
        return Base10(ln, sn, true);
    }
    friend struct Base10 operator*(const struct Base10 &ref1, const struct Base10 &ref2) {
        return Base10( ref1.n + ref2.n );
    }
    friend std::ostream& operator<<(std::ostream &os, const struct Base10 &ref) {
        os << ref.makeStr(); return os;
    }

    std::string makeStr(void) const {
        std::string result = "1";
        for (int i = 0; i < this->n; ++i) result += "0";

        if (this->has_n2) {
            if (this->n == this->n2) {
                result[result.size() - this->n2 - 1] = '2';
            } else {
                result[result.size() - this->n2 - 1] = '1';
            }
        } 

        return result;
    }
};

int main(void) {
    std::string A, B; char opchar; std::cin >> A >> opchar >> B;
    enum Operator op = (opchar == '+' ? ADD : MUL);
    struct Base10 result;
    switch(op) {
        case ADD: 
            result = Base10(A) + Base10(B);
            break;
        case MUL:
            result = Base10(A) * Base10(B);
            break;
    }
    std::cout << result << '\n';
    return 0;
}
