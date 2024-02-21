#include <iostream>

int k_Hexa(int N) {
    int k;
    //calculate which hexagon number N belongs to
    // 1     ->  0 th Hexa
    // 2 ~ 7 ->  1 th Hexa
    if (N == 1) k = 0;
    else {
        k = 1;
        int min = 2, max = 7;

        while(!(min <= N && N <= max)) {
            k++;
            // DIY: range of kth Hexa
            min = 3*k*k - 3*k + 2;
            max = 3*k*k + 3*k + 1;
        }
    }
    return k;
}

int main(void) {
    int N; std::cin >> N;
    int k = k_Hexa(N);
    // N in kth Hexa can be always approached with k + 1 hexagons.
    std::cout << k + 1 << '\n';
    return 0;
}
