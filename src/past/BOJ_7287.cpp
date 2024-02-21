#include <iostream>
#include <string>

namespace INFO {
    const std::string ID = "nachiketa3299";
    const int SOLVED = 125;
}
int main(void) {
    std::cout << INFO::SOLVED << std::endl;
    std::cout << INFO::ID << std::endl;
}
