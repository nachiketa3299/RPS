#include <iostream>
#include <string>
#include <stack>

class TString {
private:
    std::string str;
    std::stack<int> A;
    std::string S;

    struct RecurReturn {
        std::string sub_str;
        int a;
        std::string s;
        RecurReturn (void) : a(0), s(""), sub_str("") {}
        RecurReturn (const RecurReturn& to_copy) 
            : a(to_copy.a), s(to_copy.s), sub_str(to_copy.sub_str) {}
    };

public: /* Constructors... */
    TString (const std::string &str) : str(str) {
        this->initAS();
        return;
    }

private: /* Recursion Functions */
    static bool isAllSame(const std::string& str) {
        for (int i = 1; i < str.size(); i++) {
            if (str[0] != str[i]) {
                return false;
            }
        }
        return true;
    }

    RecurReturn findPossible(const std::string& str) {
        RecurReturn *recur_return = new RecurReturn();
        if (TString::isAllSame(str)) {
            recur_return->s = str.front();
            recur_return->a = str.size();
            recur_return->sub_str = "";
        } else {

            int boundary = str.size() / 2 + str.size() % 2;
            for (int i = 1; i < boundary; i++) {
                std::string pos_str = str.substr(0, i);
                std::string pos_s = str.substr(i, 1);

                if (str.size() % (pos_str.size() + pos_s.size()) == pos_str.size()) {
                    int start = pos_str.size() + 1;
                    int end = str.size() - pos_str.size();
                    int step = pos_str.size() + pos_s.size(); 
                    int a = 1;
                    bool all_checked = true;

                    for (int j = start; j < end; j += step) {
                        std::string com_str = str.substr(j, pos_str.size());
                        std::string com_s = str.substr(j + pos_str.size(), 1);

                        if (pos_str != com_str || pos_s != com_s) {
                            all_checked = false;
                            break;
                        }
                        a++;
                    }

                    if (all_checked == true) {
                        std::string com_last_str = str.substr(str.size() - pos_str.size(), pos_str.size());
                        if (com_last_str != pos_str) {
                            all_checked = false;
                        }
                    }

                    if (all_checked == true) {
                        recur_return->s = pos_s;
                        recur_return->a = a;
                        recur_return->sub_str = pos_str;
                        break;
                    }
                }
            }
        }
        return *recur_return;
    }

    void initAS (void) {
        this->recursion(this->str);
        return;
    }

    void recursion (const std::string& sub_str) {
        RecurReturn recur_return(this->findPossible(sub_str));
        if (recur_return.sub_str.size() == 0) {
            this->S = recur_return.s + this->S;
            this->A.push(sub_str.size());
            return;
        } else {
            this->S = recur_return.s + this->S;
            this->A.push(recur_return.a);
            this->recursion(recur_return.sub_str);
        }
        return;
    }

public: /* Print Functions */
    void printA (void) {
        std::stack<int> A_copy = this->A;
        while(!A_copy.empty()) {
            std::cout << A_copy.top() << " ";
            A_copy.pop();
        }
        std::cout << '\n';
    }
    void printS (void) {
        std::cout << this->S << '\n';
    }
};

int main (void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::string t_str; std::cin >> t_str;
    TString T (t_str);

    T.printS();
    T.printA();

    return 0;
}
