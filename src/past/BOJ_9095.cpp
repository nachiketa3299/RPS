#include <iostream>
int fact(int n) {
    int r = 1;
    for (std::size_t i = 1; i <= n; ++i) r *= i;
    return r;
}

int getCountNDivide(int n) {
    int t_cnt = 0;
    for (std::size_t i = 0; i <= n / 2; ++i) {
        for (std::size_t j = 0; j <= (n - i * 2) / 3; ++j) {
            int cnt_1, cnt_2, cnt_3;
            cnt_3 = j;
            cnt_2 = i;
            cnt_1 = n - 2*cnt_2 - 3*cnt_3;
            if (cnt_1 + 2*cnt_2 + 3*cnt_3 == n) {
                int cnt_123 = cnt_1 + cnt_2 + cnt_3;
                t_cnt += fact(cnt_123) / (fact(cnt_1) * fact(cnt_2) * fact(cnt_3));
            } 
        }
    }
    return t_cnt;
}


int main(void) {
    std::ios::sync_with_stdio(false); 
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int T; std::cin >> T;
    for (std::size_t i = 0; i < T; ++i) {
        int n; std::cin >> n;
        std::cout << getCountNDivide(n) << '\n';
    }

    return 0;
}
