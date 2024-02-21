#include <iostream>
#include <string>


bool p_recur(const std::string &str, int s, int e) {
    if ( s >= e ) {
        return true;
    } else if (str[s] != str[e]) {
        return false;
    } else {
        return p_recur(str, ++s, --e);
    }
}

int isPalindrome(const std::string &str) {
    return p_recur(str, 0, str.size() - 1) ? 1 : 0;
}




int main(void) {
    std::string input; std::cin >> input;
    std::cout << isPalindrome(input) << '\n';
}
