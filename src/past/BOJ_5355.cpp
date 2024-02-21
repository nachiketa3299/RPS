#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

enum Operator { AT, MOD, SHARP };

struct Operation {
    double val; 
    std::vector<enum Operator> o_v;
    Operation(double val, std::vector<enum Operator> o_v): val(val), o_v(o_v) {}
    double getResult(void) const {
        double result = val;
        for (const auto &o: this->o_v) {
            switch(o){
                case AT:
                    result *= 3.0; break;
                case MOD:
                    result += 5.0; break;
                case SHARP:
                    result -= 7.0; break;
            }
        }
        return result;
    }
};

double opstrToOp(const std::string &opstr, std::vector<enum Operator> &op_v) {
    std::string::const_iterator it = std::find(opstr.cbegin(), opstr.cend(), ' ');
    int idx_op_begins = std::distance(opstr.cbegin(), it);
    double val = std::stod(opstr.substr(0, idx_op_begins));

    std::string cur_opstr = opstr.substr(idx_op_begins + 1);
    std::string::iterator cur_it = std::find(cur_opstr.begin(), cur_opstr.end(), ' ');

    while(cur_it != cur_opstr.end()) {
        char cur_op = cur_opstr[0];
        switch (cur_op) {
            case '@':
                op_v.push_back(AT); break;
            case '#':
                op_v.push_back(SHARP); break;
            case '%':
                op_v.push_back(MOD);break;
        }
        cur_opstr = cur_opstr.substr(2);
        cur_it = std::find(cur_opstr.begin(), cur_opstr.end(), ' ');
    }
    char cur_op = cur_opstr[0];
    switch (cur_op) {
        case '@':
            op_v.push_back(AT); break;
        case '#':
            op_v.push_back(SHARP); break;
        case '%':
            op_v.push_back(MOD);break;
    }
    return val;
}

int main(void) {
    int T; std::cin >> T; std::cin.ignore();
    std::cout << std::fixed; std::cout.precision(2);
    for (std::size_t i = 0; i < T; ++i) {
        std::string opstr; std::getline(std::cin, opstr, '\n');
        std::vector<enum Operator> op_v; double nval;
        nval = opstrToOp(opstr, op_v);
        std::cout << Operation(nval, op_v).getResult() << '\n';
    }
}
