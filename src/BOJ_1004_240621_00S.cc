// 백준 어린 왕자 1004 S3 
// 2024-06-21 12:46 24
// 2024-06-21 14:26 15:09 (34 + 9 = 43)

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

struct p2_t {
	int x, y; // in [-1'000, 1'000]
	friend istream& operator>>(istream& in, p2_t& rhs) {
		in >> rhs.x >> rhs.y;
		return in;
	}

	int ein_cnt { 0 }; // exclusive in count
};

struct psys_t {
	enum class info_t { NONE, IN, OUT };

	friend istream& operator>>(istream& in, psys_t& rhs) {
		in >> rhs.pivot >> rhs.radius;
		return in;
	}
	p2_t pivot;
	info_t info { info_t::NONE };
	int radius; // in [1, 1'000]

	float distance(p2_t const& p) const {
		auto dx = static_cast<float>(p.x - pivot.x);
		auto dy = static_cast<float>(p.y - pivot.y);
		return sqrt(dx * dx + dy * dy);
	}

};


int main() {
	int T; cin >> T; // testcases
	vector<int> outputs(T);

	for (int i = 0; i < T; ++i) {
		// input
		p2_t start, dest;
		cin >> start >> dest;

		int n; cin >> n; // in [1, 50]
		vector<psys_t> psyss(n);
		for (auto& psys: psyss)
			cin >> psys;
		// process

		// count only exclusively including point
		auto cnt_ein = [&start, &dest](psys_t const& o) {
			bool const s_in = o.distance(start) > static_cast<float>(o.radius);
			bool const d_in = o.distance(dest) > static_cast<float>(o.radius);

			return !((s_in && d_in) || (!s_in && !d_in));
		};

		outputs[i] = count_if(psyss.cbegin(), psyss.cend(), cnt_ein);
	}

	// output
	for (auto const& output: outputs)
		cout << output << '\n';
}
