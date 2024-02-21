#include <iostream>
#include <csignal>

void sigHandler(int sig) {
    std::cout << "Overflowed\n";
}

typedef long long int lli;

lli DC (lli A, lli B, lli C) {
    if      (B     == 1) return A                                         % C;
    else if (B % 2 == 0) return (DC(A, B/2, C) * DC(A, B/2, C))           % C;
    else                 return (DC(A, B/2, C) * DC(A, B/2, C) * (A % C)) % C;
}

int main(void) {
    signal(SIGABRT, &sigHandler);

    lli A, B, C; std::cin >> A >> B >> C;
    std::cout << DC(A, B, C) << std::endl;
    return 0;
}

