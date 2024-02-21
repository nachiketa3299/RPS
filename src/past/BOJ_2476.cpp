#include <iostream>
#include <vector>
#include <algorithm>

class DiceState {
private:
    std::vector<int> d_nums;
    enum State { THREE = 1, TWO = 2, NONE = 3 } state;
    int same_num;
public:
    DiceState(const std::vector<int> &d_nv): d_nums(d_nv) {
        if (this->d_nums[0] == this->d_nums[1] && this->d_nums[0] == this->d_nums[2]) {
            this->state = State::THREE;
            this->same_num = this->d_nums[0];
        } else if (this->d_nums[0] == this->d_nums[1] && this->d_nums[0] != this->d_nums[2] || this->d_nums[0] == this->d_nums[2] && this->d_nums[0] != this->d_nums[1] || this->d_nums[1] == this->d_nums[2] && this->d_nums[1] != this->d_nums[0] ) {
            this->state = State::TWO;
            if (this->d_nums[0] == this->d_nums[1]) this->same_num = this->d_nums[0];
            else if (this->d_nums[0] == this->d_nums[2]) this->same_num = this->d_nums[0];
            else this->same_num = this->d_nums[1];
        } else {
            this->state = State::NONE;
            this->same_num = 0;
        }
        return;
    }

    int calPrice(void) const {
        int price;
        switch(this->state) {
            case NONE: {
                auto it_max = std::max_element(this->d_nums.begin(), this->d_nums.end());
                price = (*it_max) * 100;
                break;
            }
            case TWO: {
                price = 1000 + this->same_num * 100;
                break;
            }
            case THREE: {
                price = 10000 + this->same_num * 1000;
                break;
            }
        }
        return price;
    }
};

int main(void) {
    int N; std::cin >> N;
    std::vector<int> prices;
    for (std::size_t i = 0; i < N; ++i) {
        int d1, d2, d3; std::cin >> d1 >> d2 >> d3;
        prices.push_back(DiceState({ d1, d2, d3 }).calPrice());
    }
    std::cout << *std::max_element(prices.begin(), prices.end()) << '\n';
    return 0;
}
