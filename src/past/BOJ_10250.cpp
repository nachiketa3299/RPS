#include <iostream>
#include <string>

class Hotel {
private:
    std::size_t floor;
    std::size_t width;
public:
    Hotel(std::size_t floor, std::size_t width): floor(floor), width(width) {}
    std::string whereTocheckIn(std::size_t pnum) const {
        return this->to_room_name(this->cal_fl_wd_n(pnum));
    }

private:
    std::string to_room_name(const std::pair<std::size_t, std::size_t> &wd_fl) const {
        const std::size_t &cwidth = wd_fl.first;
        const std::size_t &cfloor = wd_fl.second;
        std::string cfloor_str = std::to_string(cfloor);
        std::string cwidth_str;
        if (cwidth <= 9) cwidth_str = "0" + std::to_string(cwidth);
        else cwidth_str = std::to_string(cwidth);
        return cfloor_str + cwidth_str;
    }

    std::pair<std::size_t, std::size_t> cal_fl_wd_n(std::size_t pnum) const {
        std::size_t cfloor = (pnum % this->floor);
        cfloor = (cfloor == 0 ? this->floor : cfloor);
        std::size_t cwidth = ((pnum - cfloor) / this->floor) + 1;
        return { cwidth, cfloor };
    }

};

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    std::size_t T; std::cin >> T;
    for (std::size_t tidx = 0; tidx < T; ++tidx) {
        std::size_t H, W, N; std::cin >> H >> W >> N;
        std::cout << Hotel(H, W).whereTocheckIn(N) << '\n';
    }
    return 0;
}
