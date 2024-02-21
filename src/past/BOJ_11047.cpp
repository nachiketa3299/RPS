#include <iostream>
#include <vector>

std::size_t getCoinNumMin(std::size_t, std::size_t, const std::vector<int>&);

int main(void) {
    // Input N, K
    int N; std::size_t K; std::cin >> N >> K;
    std::vector<int> coin_value(N);
    // Input each coin values in **Descending** order
    for (std::size_t i = 0; i < N; ++i)
        std::cin >> coin_value[N - i - 1];

    std::cout << getCoinNumMin(K, N, coin_value) << '\n';


    return 0;
}

std::size_t getCoinNumMin(std::size_t K, std::size_t N, const std::vector<int> &coins) {
    
    // Copy value K to temporary storage
    std::size_t temp_K = K; 
    std::size_t max_coin;
    std::vector<std::size_t> coin_counts(N, 0);
    for (std::size_t i = 0; i < N; ++i) {
        // Assuming maximum coin value
        if (temp_K >= coins[i]) {
            max_coin = coins[i];
            std::size_t ccoin_cnt;
            for (ccoin_cnt = 1; max_coin * ccoin_cnt < temp_K; ++ccoin_cnt) {
                ;
            }
            coin_counts[i] = --ccoin_cnt;
            temp_K -= coin_counts[i] * max_coin;
            break;
        }
    }
    return 0;
}
