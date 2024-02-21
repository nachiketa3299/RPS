#include <iostream>

long long int g(int x) {
    long long int sum = 0;
    for (std::size_t i = 1; i <= x; ++i)
        sum += i * (x / i);
    return sum;
}

int main(void) {
    long long int N; std::cin >> N;
    std::cout << g(N) << '\n';
}

/*
 1( 1) = 1    
 2( 3) = 1 2
 3( 4) = 1   3
 4( 7) = 1 2   4
 5( 6) = 1       5
 6(11) = 1 2 3     6
 7( 8) = 1           7
 8(15) = 1 2   4       8
 9(13) = 1   3           9
10(18) = 1 2     5         10

g(10) = 1 *10 + 2 *5 + 3 *3 + 4 *2 + 5 *2

 */
