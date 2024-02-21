#include <iostream>
#include <vector>
#include <algorithm>

struct Coin { std::size_t val=0, cnt=0; };

class CoinPocket {
private:
    std::vector<Coin> *coins;
public:
    CoinPocket(std::vector<Coin> *coins): 
        coins(coins) {}

    const CoinPocket &makeTargetPriceWithCoins(std::size_t tprice) {
        std::size_t cprice = 0;
        for (Coin &ccoin: *(this->coins)) {
            ccoin.cnt = (tprice - cprice) / ccoin.val;
            cprice += ccoin.cnt * ccoin.val;
        }
        return (*this);
    }
};

int main(void) {
    std::size_t N, K; std::cin >> N >> K;
    std::vector<Coin> coin_info(N);
    for (std::size_t i = 0; i < N; ++i)
        std::cin >> coin_info[i].val;
    std::sort(coin_info.begin(), coin_info.end(), [&](const Coin &ref1, const Coin &ref2){
            return ref1.val > ref2.val;
    });

    CoinPocket CP(&coin_info);
    CP.makeTargetPriceWithCoins(K);
    std::size_t coin_cnt_sum = 0;
    for (const auto &e: coin_info) coin_cnt_sum += e.cnt;
    std::cout << coin_cnt_sum << '\n';

    return 0;
}
