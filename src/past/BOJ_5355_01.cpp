#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

enum Operator { AT, MOD, SHARP };

struct MarsOperation {
    double val; std::vector<enum Operator> ops;
    MarsOperation(double val, std::vector<enum Operator> ops)
        : val(val), ops(ops) {}
    MarsOperation(const std::string &op_str)
        : MarsOperation(MarsOperation::parseOpStr(op_str)) {}

    static struct MarsOperation parseOpStr(const std::string &top_str) {
        // top_str means total op_str (val + op_str)
        double temp_val; std::vector<enum Operator> temp_ops;

        auto fblank_it = std::find(top_str.begin(), top_str.end(), ' ');
        std::size_t fblank_idx = std::distance(top_str.begin(), fblank_it);

        temp_val = std::stod(top_str.substr(0, fblank_idx));
        std::string op_str = top_str.substr(fblank_idx + 1);

        while(true) {
            auto nblank_it = std::find(op_str.begin(), op_str.end(), ' ');
            if (nblank_it != op_str.end()) {
                std::size_t nblank_idx = std::distance(op_str.begin(), nblank_it);
                std::string cop_str = op_str.substr(0, nblank_idx);
                temp_ops.push_back(MarsOperation::strOpToEnum(cop_str));
                op_str = op_str.substr(nblank_idx + 1);
            } else {
                temp_ops.push_back(MarsOperation::strOpToEnum(op_str));
                break;
            }
        };

        return MarsOperation(temp_val, temp_ops);
    }

    static enum Operator strOpToEnum(const std::string &op_str) {
        if (op_str == "@") return AT;
        else if (op_str == "#") return SHARP;
        else return MOD;
    }

    double getResult(void) const {
        double result = this->val;
        for (const auto &op: this->ops) {
            switch(op) {
                case AT:
                    result *= 3; break;
                case MOD:
                    result += 5; break;
                case SHARP:
                    result -= 7; break;
            }
        }
        return result;
    }
};

int main(void) {
    // input: # of testcases
    int T; std::cin >> T; std::cin.ignore();

    std::cout << std::fixed; std::cout.precision(2);
    
    // IPO per testcases
    for (std::size_t i = 0; i < T; ++i) {
        // Input raw string 
        std::string op_str; std::getline(std::cin, op_str, '\n');
        std::cout << MarsOperation(op_str).getResult() << '\n';
    }
    return 0;
}
