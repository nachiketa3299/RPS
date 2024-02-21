#include <iostream>
#include <string>
#include <stack>
struct Solution {
    std::stack<int> A;
    std::stack<char> S;
    void printA (void) {
        while(!A.empty()) {
            std::cout << this->A.top() << " ";
            this->A.pop();
        }
    }
    void printS (void) {
        while(!S.empty()) {
            std::cout << this->S.top() << " ";
            this->A.pop();
        }
    }
};

void findASRecur (const std::string& str, struct Solution& sol) {
    if (false) {

    } else {
        for (int i = 0; i < str.size(); i++) {
            std::string pos_x = str.substr(0, i + 1);
            char pos_s = str[pos_x.size()];

            int start_point = pos_x.size() + 1;
            int end_point = str.size() - 1 - pos_x.size();
            int step = pos_x.size() + 1;

            int cnt_s = 0;

            for (int j = start_point; j <  end_point; j += step) {
                std::string com_x = str.substr(j, pos_x.size());
                if (pos_x == com_x && str[j + pos_x.size()] == pos_s) {
                    cnt_s++;
                } else {
                    break;
                }
            }
            
            sol.A.push(cnt_s);
            sol.S.push(pos_s);
        }
    }
}

struct Solution& findAS (const std::string& str) {
    struct Solution* sol = new struct Solution;
    findASRecur(str, *sol);
    return *sol;
}


int main (void) {
    std::string T;
    std::cin >> T;
    std::stack<int> A;
    std::stack<char> S;
    struct Solution sol = findAS(T);
    sol.printS();
    sol.printA();


    return 0;
}
