#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using T_Val = int;
using T_Freq = int;

struct FreqData
{
    FreqData(const T_Val& val) : val(val) {};
    T_Val val;
    T_Freq freq = 1;
    friend ostream& operator<<(ostream& out, const FreqData& fdata)
    {
        for ( T_Freq i = 0; i < fdata.freq; ++i) out << fdata.val << " ";
        return out;
    }

    bool operator==(const FreqData& data) { return this->val == data.val; };
};

int main(void)
{
    int msg_len; cin >> msg_len; //< `msg_len` in [1, 1e3]
    T_Val msg_max_val; cin >> msg_max_val; //< `msg_max_val` in [1, 1e9]

    vector<FreqData> fvec;
    for (int i = 0; i < msg_len; ++i)
    {
        T_Val tval; cin >> tval;
        auto fpos = find(fvec.begin(), fvec.end(), tval);

        if (fpos == fvec.end())
        {
            fvec.emplace_back(FreqData(tval));
            continue;
        }
        ++fpos->freq;
    }
    //stable_sort(fvec.cbegin(), fvec.cend(), less<FreqData>());
    for (const auto & f: fvec) cout << f;
}