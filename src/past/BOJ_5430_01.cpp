#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

enum CMD { Rev, Fo, Ba };

class Command {
private:
    std::vector<CMD> vec;
    //std::size_t d_cnt, r_cnt;
    std::size_t rev_cnt = 0;
public:
    Command(std::string str) {
        str = this->erase_consecutive_R(str);
        std::cout << str << std::endl;
        str = this->optimize_commands(str);
        this->vec = this->make_command(str);
    }
    const std::vector<CMD> &getCommand(void) const {
        return this->vec;
    }
    const std::size_t getRevCount(void) const {
        return this->rev_cnt;
    }
private:
    std::vector<CMD> make_command(const std::string &str) {
        std::vector<CMD> cmdv;
        for (const char &c: str) {
            switch(c) {
                case 'R':
                    cmdv.push_back(Rev);
                    this->rev_cnt++;
                    if(this->rev_cnt == 2) this->rev_cnt = 0;
                    break;
                case 'F':
                    cmdv.push_back(Fo);
                    break;
                case 'B':
                    cmdv.push_back(Ba);
                    break;
            }
        }
        return cmdv;
    }

    std::string erase_consecutive_R(std::string &str) {
        //std::cout << "First String: " << str << std::endl;
        std::string temp_r; // temporary R;
        std::string r_str;
        for (std::size_t i = 0; i < str.size(); ++i) {
            if (str[i] == 'D') {
                r_str += temp_r + str[i];
                temp_r.clear();
            } else {
                temp_r += str[i];
                if (temp_r.size() == 2) temp_r.clear();
            }
        }
        return r_str + temp_r;
    }

    std::string optimize_commands(std::string &str) {
        //std::cout << "Original String: " << str << std::endl;
        std::string ostr = "";
        std::size_t r_cnt = 0; // number of r;

        std::size_t sidx = 0;
        std::size_t ridx = str.find('R');
        std::string convop = "";

        while(ridx != std::string::npos) {
            r_cnt++;
            switch(r_cnt) {
                case 1:
                    convop = "F";
                    break;
                case 2:
                    convop = "B";
                    r_cnt = 0;
                    break;
            }

            for (std::size_t i = sidx; i < ridx; ++i) {
                ostr += convop;
            }

            if (ridx + 1 < str.size()) {
                str = str.substr(ridx + 1);
                ridx = str.find('R');
            } else {
                str = str.substr(ridx);
                ridx = std::string::npos;
            }
        }

        if (str == "R") ostr += "R";
        else {
            switch(r_cnt) {
                case 1:
                    convop = "B";
                    break;
                case 0:
                    convop = "F";
                    break;
            }
            for (const char &c: str) ostr += convop;
        }

        //std::cout << "Optimized String: " << ostr << std::endl;

        return ostr;
    }
};

class Array {
private:
    std::vector<int> vec;
public:
    Array(std::string str) {
        str.erase(str.find('['), 1); str.erase(str.find(']'), 1);
        std::size_t sidx = 0;
        auto cidx = str.find(',');
        while (cidx != std::string::npos) {
            this->vec.push_back(std::stoi(str.substr(sidx, cidx - sidx)));
            str = str.substr(cidx + 1);
            sidx = 0; cidx = str.find(',');
        }
        this->vec.push_back(std::stoi(str));
        return;
    }

    void print(void) const {
        std::cout << "[";
        for (std::size_t i = 0; i < this->vec.size(); ++i)
            std::cout << this->vec[i] << (i != this->vec.size() - 1 ? "," : "");
        std::cout << "]";
        return;
    }

    void reverse(void) {
        std::reverse(this->vec.begin(), this->vec.end());
        return;
    }
    void pop_front(void) {
        this->vec.erase(this->vec.begin());
        return;
    }
    void pop_back(void) {
        this->vec.erase(--this->vec.end());
        return;
    }
};

class Handler {
private:
    Array *arr;
    Command *cmd;
public:
    Handler(Array *arr, Command *cmd): arr(arr), cmd(cmd) {}
    Handler &process(void) {
        const std::vector<CMD> &cmds = this->cmd->getCommand();
        std::cout << "- RevCount: " << this->cmd->getRevCount() << std::endl;
        for (const CMD &cmd: cmds) {
            switch(cmd) {
                case Rev:
                    break;
                case Fo:
                    this->arr->pop_front();
                    break;
                case Ba:
                    this->arr->pop_back();
                    break;
            }
        }
        if (this->cmd->getRevCount() == 1) this->arr->reverse();
        return *this;
    }
    void printArray(void) const {
        this->arr->print();
        return;
    }
};


int main(void) {
    int T; std::cin >> T;
    for (std::size_t i = 0; i < T; ++i) {
        std::string cmd_str; std::cin >> cmd_str;
        std::size_t arr_size; std::cin >> arr_size; // Why Size..? 
        std::string arr_str; std::cin >> arr_str;
        Handler(new Array(arr_str), new Command(cmd_str)).process().printArray();
    }
    return 0;
}
