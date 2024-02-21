#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Array {
private:
    std::vector<int> arr;
    bool error = false;
    enum CommandType { R, D };
    // after Commands instance constructed, reinterpret cmds
    // shape is always [R], [D], [RDDR] (no R is repeated)
    enum OCommandType { Rev, pF, pB };
    // D -> pF (pop Front)
    // RDR -> pF (pop Back)

    class Commands {
    private:
        std::vector<CommandType> cmds;
        std::vector<OCommandType> ocmds;
        std::size_t d_cnt = 0, r_cnt = 0;
    public: // Constructor
        Commands(std::string cmd_str) {
            std::vector<CommandType> r_temp;
            for (const char &c: cmd_str) {
                switch(c) {
                    case 'R':
                        r_temp.push_back(CommandType::R);
                        if (r_temp.size() == 2) r_temp.clear();
                        break;
                    case 'D':
                        for (const auto &r: r_temp) {
                            this->cmds.push_back(r);
                            this->r_cnt++;
                        } 
                        this->cmds.push_back(CommandType::D);
                        this->d_cnt++;
                        r_temp.clear();
                        break;
                }
            }
            if (this->d_cnt == 0) {
                for (const auto &r: r_temp) {
                    this->cmds.push_back(r);
                    this->r_cnt++;
                }
            }
            std::cout << "Commands: ";
            for (const auto &e: this->cmds) {
                switch(e) {
                    case R:
                        std::cout << "R";
                        break;
                    case D:
                        std::cout << "D";
                        break;
                }
                std::cout << " ";
            }
            std::cout << std::endl;

            // TODO reinterprete this->cmds to make this->ocmds
            auto Sit = this->cmds.begin();
            auto Rit = std::find(Sit, this->cmds.end(), CommandType::R);

            while (Rit != this->cmds.end()) {
            // cmd R has found
                for (auto it = Sit; it != Rit; ++it)
                    this->ocmds.push_back(OCommandType::pF);
                std::size_t Ridx = std::distance(this->cmds.begin(), Rit);
                if (Ridx + 2 < this->cmds.size()) {
                    Sit = Rit + 3;
                    if (this->cmds[Ridx + 2] == CommandType::R)
                        this->ocmds.push_back(OCommandType::pB);
                    else {
                        for (std::size_t i = Ridx; i < Ridx + 3; ++i) {
                            switch(this->cmds[i]) {
                                case CommandType::R:
                                    this->ocmds.push_back(OCommandType::Rev);
                                    break;
                                case CommandType::D:
                                    this->ocmds.push_back(OCommandType::pF);
                                    break;
                            }
                        }
                    }
                    Rit = std::find(Sit, this->cmds.end(), CommandType::R);
                    Sit = Rit;
                } else {
                    for (std::size_t i = Ridx; i < this->cmds.size(); ++i) {
                        switch(this->cmds[i]) {
                            case CommandType::R:
                                this->ocmds.push_back(OCommandType::Rev);
                                break;
                            case CommandType::D:
                                this->ocmds.push_back(OCommandType::pF);
                                break;
                        }
                    }
                    break;
                }
            }
            
            if (Rit != this->cmds.end()) {
                // cmd R has not found -> all D -> push all pF
                for (std::size_t i = 0; i < this->cmds.size(); ++i)
                    this->ocmds.push_back(OCommandType::pF);
            }
            // Debug
            std::cout << "OCommnads: ";
            for (const auto &e: this->ocmds) {
                switch(e) {
                    case Rev:
                        std::cout << "Rev";
                        break;
                    case pF:
                        std::cout << "pF";
                        break;
                    case pB:
                        std::cout << "pB";
                        break;
                }
                std::cout << " ";
            } 
            std::cout << std::endl;
            //

            return;
        }
    public:
        const std::vector<CommandType> &getCommands(void) const { 
            return this->cmds; 
        }
        const std::vector<OCommandType> &getOCommands(void) const {
            return this->ocmds;
        }
        std::size_t getDCount(void) const { return this->d_cnt; }
    };

public: // Constructor
    Array(std::string arr_str) {
        this->arr = this->parseInputStr(arr_str);
        return;
    }
private:
    std::vector<int> parseInputStr(std::string &str) {
        std::vector<int> narr;
        // Erase '[' & ']'
        str.erase(str.find('['), 1); 
        str.erase(str.find(']'), 1); 
                                                 
        std::size_t comma_idx = str.find(',');
        while(comma_idx != std::string::npos) {
            narr.push_back(std::stoi(str.substr(0, comma_idx)));
            str = str.erase(0, comma_idx + 1);
            comma_idx = str.find(',');
        }
        if (str.size() != 0) narr.push_back(std::stoi(str));
        return narr;
    }
public: // Methods
    Array &processCommandStr(std::string cmd_str) {
        Commands cmds = Commands(cmd_str);
        if (cmds.getDCount() > this->arr.size()) {
            this->error = true;
        } else {
            for (const OCommandType &ocmd: cmds.getOCommands()) {
                switch(ocmd) {
                    case OCommandType::Rev:
                        this->fRev();
                        break;
                    case OCommandType::pF:
                        this->fpF();
                        break;
                    case OCommandType::pB:
                        this->fpB();
                        break;
                }
            }
        }
        return *(this);
    }
    void printSelf(void) const {
        if (this->error) std::cout << "error";
        else {
            this->printArray();
        }
        std::cout << std::endl;
        return;
    }
private:
    void fRev(void) {
        std::reverse(this->arr.begin(), this->arr.end());
        return;
    }

    void fpF(void) {
        this->arr.erase(this->arr.begin());
        return;
    }
    void fpB(void) {
        this->arr.erase(--this->arr.end());
        return;
    }

    void printArray(void) const {
        std::cout << "[";
        for (std::size_t i = 0; i < this->arr.size(); ++i) {
            if (i != this->arr.size() - 1)
                std::cout << arr[i] << ",";
            else 
                std::cout << arr[i];
        }
        std::cout << "]";
        return;
    }
};

int main(void) {
    int T; std::cin >> T; //get n of Testcases
    for (std::size_t t = 0; t < T; ++t) {
        std::string cmd_str; std::cin >> cmd_str;
        int arr_size; std::cin >> arr_size;
        std::string arr_str; std::cin >> arr_str;
        Array(arr_str).processCommandStr(cmd_str).printSelf();
    }
    return 0;
}
