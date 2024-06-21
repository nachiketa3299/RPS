/// 2024-06-21 12:41-02:10 (129)
/// 크로아티아 알파벳 2941 S5 

#include <iostream>
#include <string>
#include <map>
#include <cstddef>
#include <numeric>

#define DELI '*'

using namespace std;

map<string const, size_t> dict {
	{ "c=", 0 }, { "c-", 0 }, { "dz=", 0 }, 
	{ "d-", 0 }, { "lj", 0 }, { "nj" , 0 }, 
	{ "s=", 0 }, { "z=", 0 }
};

int main() { 

	auto const in_str = []() { string _t; cin >> _t; return _t; }();
	auto str = string(in_str);

	for (auto& [l, c]: dict) { 
		auto n = string::size_type { 0 };
		while ( (n = str.find(l, n)) != string::npos) {
			str.replace(n, l.length(), string(l.length(), DELI));
			n += l.length();
			++c;
		}
	}

	auto cnt_palpha = [](size_t const& a, char const& c) {
		return c != DELI ? a + 1 : a;
	};
	auto const palpha = accumulate(str.cbegin(), str.cend(), 0 , cnt_palpha);

	auto cnt_kalpha = [](size_t const& a, pair<string const, size_t> const& o) {
		auto const& [_, c] = o;
		return a + c;
	};

	auto const ret = accumulate(dict.cbegin(), dict.cend(), 0, cnt_kalpha);
	cout << ret + palpha;
}