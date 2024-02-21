// title: 백준 카드 11652 S4
// date: 2024-01-17 30

#define PS_DEBUG
//#undef PS_DEBUG

#include <map>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
struct Count_t {
    size_t cnt = 0;

    bool operator==(const Count_t& other) const {
        return cnt == other.cnt;
    }
    bool operator!=(const Count_t& other) const {
        return !(*this == other);
    }
    bool operator<(const Count_t& other) const {
        return cnt < other.cnt;
    }
    bool operator>(const Count_t& other) const {
        return cnt > other.cnt;
    }
    Count_t& operator++() {
        ++cnt;
        return *this;
    }
};

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int N; cin >> N;
    using Card_t = long long int;
    map<Card_t, Count_t> m;

    for (size_t i = 0; i < N; ++i) {
        Card_t c_card; cin >> c_card;
        ++m[c_card];
    }

    using map_kv_pair = pair<Card_t, Count_t>;
    vector< map_kv_pair > vec(m.begin(), m.end());
    static const auto count_desc_pred = [](const map_kv_pair& pl, const map_kv_pair& pr){ 
        const auto& [l_card_n, l_card_cnt] = pl;
        const auto& [r_card_n, r_card_cnt] = pr;

        if (l_card_cnt != r_card_cnt)
            return l_card_cnt > r_card_cnt;
        else
            return l_card_n < r_card_n;
    };
    sort(vec.begin(), vec.end(), count_desc_pred);

    const auto& [sol_card_n, sol_card_cnt] = vec.front();
    cout << sol_card_n;

    return 0;
}