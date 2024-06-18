/// @date 2024-06-18T15:56--16:25 (29)

#include <iostream>
#include <vector>
#include <array>

using namespace std;
using wb_t = array<array<bool, 100>, 100>;

void add_box(wb_t& wb, pair<int, int> const& pos) {
	auto const& [bi, bj] = pos;

	for (int i = bi; i < bi + 10; ++i) {
		for (int j = bj; j < bj + 10; ++j) {
			if (wb[i][j]) continue;
			else wb[i][j] = true;
		}
	}
}

int get_area(wb_t const& wb) {
	int a = 0;
	for (int i = 0; i < wb.size(); ++i) {
		for (int j = 0; j < wb.front().size(); ++j) {
			if (wb[i][j]) ++a;
		}
	}
	return a;
}
void print(wb_t const& wb) {
	for (int i = 0; i < wb.size(); ++i) {
		for (int j = 0; j < wb.front().size(); ++j) {
			if (wb[i][j]) cout << 'R';
			else cout << '.';
		}
		cout << '\n';
	}
	cout << '\n';
}

int main() {
	int wc; cin >> wc;
	vector<pair<int, int>> poss(wc);
	for (auto& pos: poss) cin >> pos.first >> pos.second;


	auto wb  = wb_t { {false} };
	for (auto const& pos: poss) {
		add_box(wb, pos);
	}
	// print(wb);
	
	cout << get_area(wb);
}