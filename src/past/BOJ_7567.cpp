#include <iostream>
#include <string>
int calTotalHeight(std::string bi) {
    int t_height = 10;
    for (int i = 1; i < bi.size(); i++) {
        if (bi[i] == bi[i - 1]) t_height += 5;
        else t_height += 10;
    }
    return t_height;
}

int main(void) {
    std::string bowl_input;
    std::cin >> bowl_input;
    std::cout << calTotalHeight(bowl_input) << std::endl;
    return 0;
}
