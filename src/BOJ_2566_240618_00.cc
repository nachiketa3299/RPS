/// @date 2024-06-18T15:30--15:42 (12)

#include <iostream>
#include <array>
#include <algorithm>

using namespace std;

int main() {
	constexpr int kNINE = 9;

	array<int, kNINE * kNINE> bb;
	auto idx = [&kNINE](int const& i, int const& j) { 
		return kNINE * i + j; 
	}; 

	for (int i = 0; i < kNINE; ++i)
		for (int j = 0; j < kNINE; ++j)
			cin >> bb[idx(i, j)]; // in [0, 100]

	auto const mit = max_element(bb.begin(), bb.end());
	auto const bbidx = distance(bb.begin(), mit);

	auto iidx = [&kNINE](int const& ii) {
		return make_pair(ii / kNINE, ii % kNINE);
	};

	auto [i, j] = iidx(bbidx);
	cout << *mit << '\n' << ++i << ' ' << ++j;
}