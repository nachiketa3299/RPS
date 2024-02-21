// [2023-10-20T12:59, 2023-10-20T14:07] (68)

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
using ulint = unsigned long int;

struct Freq_Data {
    Freq_Data(const ulint& ival): val(ival) {};
    ulint val { 0 };
    size_t freq { 1 };
    bool operator==(const ulint& ref) const { return (this->val == ref); };
};

int main(void) {
    size_t msg_len; cin >> msg_len; //< `msg_len` in [1, 1e3]
    ulint max_val; cin >> max_val; //< `max_val` in [1, 1e9]

    vector<Freq_Data> fvec;
    for (size_t i = 0; i < msg_len; ++i) {
        ulint tval; cin >> tval;
        auto fpos = find(fvec.begin(), fvec.end(), tval);

        if (fpos == fvec.end()) fvec.push_back(Freq_Data(tval));
        else (fpos->freq)++;
    }

    using CFDR = const Freq_Data&;
    stable_sort(fvec.begin(), fvec.end(), [](CFDR r1, CFDR r2) {return r1.freq > r2.freq; });
    for (const auto& f : fvec) {
        for (size_t i = 0; i < f.freq; ++i) {
            cout << f.val << ' ';
        }
    }

    return 0;
}