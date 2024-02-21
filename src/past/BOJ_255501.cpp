#include <iostream>
#include <string>
#include <vector>

static int recursion_call;

bool recursion (const std::string &str, int h, int t) {
    recursion_call++;
    if (h >= t) {
        return true;
    } else if (str[h] != str[t]) {
        return false;
    } else {
        return recursion(str, h + 1, t - 1);
    }
}

bool isPalindrome (const std::string& str) {
    recursion_call = 0;
    return recursion(str, 0, str.size() - 1);
}

int main (void) {
    int T;
    std::cin >> T;
    std::vector<std::string> testcases;
    for (int i = 0; i < T; i++) {
        std::string str_temp;
        std::cin >> str_temp;
        testcases.push_back(str_temp);
    }

    for (int i = 0; i < T; i++) {
        std::cout << isPalindrome(testcases[i]) << " ";
        std::cout << recursion_call << std::endl;
    }
}
