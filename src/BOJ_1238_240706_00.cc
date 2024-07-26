// 백준 파티 G3 1238 12:49 1:21 (32)

#include <iostream>
#include <tuple>
#include <vector>
#include <queue>
#include <numeric>
#include <algorithm>

using namespace std;

using adj_t = pair<int, int>; // weight, index;

int min_dist(vector<vector<adj_t>> const& adj_list, int start, int dest) {
	auto dists = vector<int>(adj_list.size(), numeric_limits<int>::max());
	auto to_visit =
		priority_queue<adj_t, vector<adj_t>, greater<adj_t>>();
	dists[start] = 0;
	to_visit.push(adj_t{dists[start], start});

	while(!to_visit.empty()) {
		auto const [cdist, cv] = to_visit.top();
		to_visit.pop();

		if (cv == dest) {
			return cdist;
		}

		for (auto const& [adist, av]: adj_list[cv]) {
			auto const candid_dist = cdist + adist;

			if (candid_dist >= dists[av]) {
				continue;
			}

			dists[av] = candid_dist;
			to_visit.push(adj_t {dists[av], av});
		}
	}

	return dists[dest];
}


int main() {
	// N in [1, 1'000], M in [1, 10'000], X in [1, N]
	int N, M, X; cin >> N >> M >> X;

	using edge_t = tuple<int, int, int>; // start, dest, weight

	auto roads = vector<edge_t>(M);

	for (auto& [start, dest, weight]: roads) {
		cin >> start >> dest >> weight;
		--start; --dest; // make index
	}

	auto adj_list = vector<vector<adj_t>>(N, vector<adj_t>());

	for (auto const& [start, dest, weight]: roads) {
		adj_list[start].push_back(adj_t {weight, dest});
	}

	auto tdist_results = vector<int>(N);

	for (auto i = 0; i < N; ++i) {
		tdist_results[i] = min_dist(adj_list, i, X - 1) + min_dist(adj_list, X - 1, i);
	}

	cout << *max_element(begin(tdist_results), end(tdist_results));
}