/// @date 2024-06-18T14:55 -- 15:06 (11)
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>

using namespace std;

void reverse_ij(vector<int>& ns, pair<int, int> const& w) {
	auto const& [ i, j ] = w;
	auto f = ns.begin() + i - 1;
	auto l = ns.begin() + j;
	reverse(f, l);
}

int main() {
	int N, M; cin >> N >> M; // N, M in [1, 100]

	vector<int> ns(N);  iota(ns.begin(), ns.end(), 1);

	vector<pair<int, int>> ws;
	for (int i = 0; i < M; ++i) {
		int ti, tj; cin >> ti >> tj;
		ws.push_back({ ti, tj });
	}

	for (auto const& w: ws) {
		reverse_ij(ns, w);
	}

	for (auto const& n: ns) 
		cout << n << ' ';
}
