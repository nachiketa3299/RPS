#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>

using namespace std::chrono;

int main(void) {

    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d");
    std::cout << ss.str() << std::endl;

    return 0;
}
