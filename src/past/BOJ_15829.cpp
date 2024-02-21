#include <iostream>
#include <string>
#include <vector>

long long int hashFunc(std::string &str) {
    const int r = 31; const long long int M = 1'234'567'891;
    std::vector<std::size_t> seq(str.size());
    for (std::size_t i = 0; i < str.size(); ++i) {
        // Convert char to sequence int
        seq[i] = str[i] - 'a' + 1;
    }

    // now vector seq has numeric sequence of string

    long long int sum = 0;
    for (std::size_t i = 0; i < seq.size(); ++i) {
        long long int coeff_r = 1; // r^0
        for (std::size_t j = 0; j < i; ++j) {
            coeff_r *= r;
            coeff_r %= M;
        }
        coeff_r %= M;

        for (std::size_t j = 0; j < seq[i]; ++j) {
            sum += coeff_r;
            sum %= M;
        }
        sum %= M;
        /*
        std::cout << "q: " << seq[i] << '\n';
        std::cout << "i: " << i << '\n';
        std::cout << "c: " << coeff_r << '\n';
        std::cout << "s: " << sum << '\n';
        std::cout << "C: " << 1234567891 << '\n';
        std::cout << '\n';
        */
    }

    return sum;
}

int main(void) {
    int L; std::cin >> L;             // input L
    std::string str; std::cin >> str; // input str
    //std::string str = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxy";

    std::cout << hashFunc(str) << std::endl;
    return 0;
}
