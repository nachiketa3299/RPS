#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>

namespace CONST{
    const char BRC_R = ']';
    const char BRC_L = '[';
    const char COMMA = ',';
    const char RCHAR = 'R';
    const char DCHAR = 'D';
    const int RV = -1; // RV is for the direction of array
}

enum COMMAND { PB, PF };
// Command PB is Popping element from last  (pop_back)
// Command PF is Popping element from first (pop_front)

struct Command {
    /* Struct that parses command string, holds interpreted commands */
    std::vector<COMMAND> vec;
    std::size_t          r_cnt = 0;
    std::size_t          d_cnt = 0;
    Command(const std::string &str) {
        // Parsing command string to COMMAND vector
        // with Rcount
        using namespace CONST;
        int csign = 1;
        for (const char &c: str) {
            switch(c) {
                case RCHAR:
                    csign *= RV;
                    this->r_cnt++;
                    if (r_cnt >= 2) r_cnt = 0;
                    // r_cnt over 2 is meaningless
                    break;
                case DCHAR:
                    switch(csign) {
                        case 1:
                            // array is not reversed so popping from front
                            this->vec.push_back(COMMAND::PF);
                            break;
                        case -1:
                            // array is reversed, so popping from last
                            this->vec.push_back(COMMAND::PB);
                            break;
                    }
                    this->d_cnt++; // 'D' command must be counted because of error flag
                    break;
            }
        }
        return;
    }
    ~Command(void) {}
};

struct Array {
    /* Struct that parses input array string, holds the data of array, prints with requirements */
    std::deque<int> deq; // Data should be deque, because operations are only performed in front/back of data structure
    std::size_t     size; // I will not use size() memb func, because of time complexity issue

    Array(const std::string &str, std::size_t size): size(size) {
        if (this->size == 0) return; // If input array size = 0, DO NOTHING and return (no data)

        using namespace CONST;
        // Parsing string with iterator
        std::string temp_intstr = ""; // temporary variable for holding values
        for (auto sit = str.begin(); sit != str.end(); ++sit) {
            const char &cchar = (*sit); // cchar: currently looking character
            if (cchar == BRC_L || cchar == BRC_R) {
                //do nothing
            } else if (cchar != COMMA) {
                temp_intstr += cchar;
            } else if (cchar == COMMA) {
                this->deq.push_back(std::stoi(temp_intstr));
                temp_intstr.clear();
            } 

            if (sit + 1 == str.end()) {
                // for the string after last comma
                this->deq.push_back(std::stoi(temp_intstr));
                temp_intstr.clear();
            }
        } 
        return;
    }
    ~Array(void) {}
    void print(bool reversed=false) const {
        // If handler says this array is reversed, dont' reverse the array in real,
        // just printing it in reverse order for the sake of time cost.
        using namespace CONST;
        std::cout << BRC_L;
        if (reversed) {
            for (std::size_t i = 0; i < this->size; ++i) {
                std::cout << this->deq[size - i - 1];
                if (i != this->size - 1) std::cout << ",";
            }
        } else {
            for (std::size_t i = 0; i < this->size; ++i) {
                std::cout << this->deq[i];
                if (i != this->size - 1) std::cout << ",";
            }
        }
        std::cout << BRC_R;
        return;
    }
    void pop_front(void) {
        // Poping one element in front of this array
        this->deq.pop_front();
        this->size--;
        return;
    }
    void pop_back(void) {
        // Poping one element in ths back of this array
        this->deq.pop_back();
        this->size--;
        return;
    }
};

class Handler {
    /* Handler directs & manages Array and Command struct */
    /* Processes Commands to Array and holds informations like error, reversed */
private:
    Array   *arr;
    Command *cmd;
    bool    error    = false;
    bool    reversed = false;
public:
    Handler(Array *arr, Command *cmd): arr(arr), cmd(cmd) {}

    ~Handler (void) {
        delete this->arr;
        delete this->cmd;
        return;
    }

    Handler &process(void) {
        if (this->cmd->d_cnt > this->arr->size) {
            // If D's count is greater than array size, dont' ever process anything
            // just on error flag
            this->error = true;
        } else {
            const std::vector<COMMAND> &cmds = this->cmd->vec;
            for (const COMMAND &cmd: cmds) {
                // Caution: there's no Reverse operation
                switch(cmd) {
                    case COMMAND::PF:
                        this->arr->pop_front();
                        break;
                    case COMMAND::PB:
                        this->arr->pop_back();
                        break;
                }
            }
            // Using r_cnt to judge whether array is reversed or not
            if (cmd->r_cnt % 2 == 1) this->reversed = true;
        }
        return *(this);
    }

    void printArray(void) const {
        // if error flag says it is error, then print error string
        if (error) std::cout << "error";
        else {
            this->arr->print(this->reversed);
        } 
        std::cout << '\n';
        return;
    }
};

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int T; std::cin >> T;
    for (std::size_t i = 0; i < T; ++i) {
        std::string cmd_str; std::cin >> cmd_str;
        std::size_t arr_size; std::cin >> arr_size;
        std::string arr_str; std::cin >> arr_str;
        Handler(new Array(arr_str, arr_size), new Command(cmd_str)).process().printArray();
    }
    return 0;
}
