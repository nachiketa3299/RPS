/// 백준 5622 B2 다이얼
/// 2024-06-20 11:59--12:31

#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

static constexpr char m[26] = {
	2, 2, 2,
	3, 3, 3,
	4, 4, 4,
	5, 5, 5,
	6, 6, 6,
	7, 7, 7, 7,
	8, 8, 8,
	9, 9, 9, 9,
};

int min_time(string const& str) {
	static auto accum = [](int l, char r) { 
		auto num = m[r - 'A'] + 1;
		return l + num;
	};
	return accumulate(str.cbegin(), str.cend(), 0, accum);
}

int main() {
	string w; cin >> w; // w.size in [2, 15]
	cout << min_time(w);
}