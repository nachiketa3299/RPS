#include <iostream>
#include <string>
#include <algorithm>


int main(void) {
    for (std::size_t i = 0; i < 3; ++i) {
        std::string i_str;
        std::getline(std::cin, i_str);
        std::transform(i_str.begin(), i_str.end(), i_str.begin(), [](std::string &i_str){
            i_str.erase(std::remove_if(i_str.begin(), i_str.end(), std::isspace), i_str.end());
            return end;
        }
    }

    return 0;
}
